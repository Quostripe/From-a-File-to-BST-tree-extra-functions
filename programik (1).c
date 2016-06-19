
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//zalozenie: liczby w pliku oddzielone spacjami i sie nie powtarzaja

struct tree{
    int key;
    struct tree* left;
    struct tree* right;
};
//funkcja dodaj¹ca do drzewa
void rek(struct tree** root, int x){
    if(*root==NULL){
        *root=(struct tree*)malloc(sizeof(struct tree));
        if(*root){                                          //mo¿e nie byc pamieci na stworzenie roota
            (*root)->key=x;
            (*root)->left=NULL;
            (*root)->right=NULL;
        }
        else
            printf("Nie mozna stworzyc drzewa BST.");
    }
    else{
        if(x>(*root)->key)
            rek(&(*root)->right,x);
        else
            rek(&(*root)->left,x);
    }
}
//funkcja ktora do³¹cza liczby z pliku do drzewa(bazuj¹cy na funkcji "rek")
void addFromFile(const char* fName, struct tree**root){
    FILE * file = fopen(fName,"rt");
    int x;
    if(file==0)                                      //gdy plik siê nie otworzy
    {
        printf("Wystapil blad z plikiem.");
    }
    else{
        while(feof(file)==0)                         //dopoki nie osiagniemy znaku konca pliku
        {
           fscanf(file,"%d", &x);                    //wywolanie funkcji dla kazdej liczby w pliku
           rek(root,x);
        }
        printf("\nGotowe.");
    }
    fclose(file);
}
//funkcja ktora liczy wezly w drzewie
int countNodes(struct tree* root){
   if (root != NULL){
         return 1+countNodes(root->left)+countNodes(root->right);
   }
   else
       return 0;
}

//funkcja która zamieni lewe poddrzewo z prawym poddrzewem.
void changeSubtree(struct tree**root, const char *fName, struct tree* temp){
    if(fopen(fName,"rt")!=0){                        //gdy plik sie otworzyl(drzewo istnieje)
        if(!(*root)) return;
        changeSubtree(&(*root)->left,fName, temp);
		changeSubtree(&(*root)->right,fName, temp);
        temp=(*root)->right;
        (*root)->right=(*root)->left;
        (*root)->left=temp;
        
    }
    else{
        printf("\nDrzewo nie istnieje.\n");
    }
}
//funkcja wizualizacyjna
void visual(struct tree *root, int space){
	int i;
	if (root == NULL)
		return;
    space += 4;

	visual(root->right, space);
	printf("\n");

    for (i = 4; i < space; i++)
        printf(" ");

    printf("%d\n", root->key);
    visual(root->left, space);
}
int main()
{
	struct tree* temp;
    struct tree* root=NULL;
    int k=0;          //zapamietuje wybor uzytkownika
    int p=0;          //czy drzewo jest stworzone
    int m=0;          //=1 gdy uzytkownik chce wyjscz pêtli
    int elem=0;       //ilosc wezlow
    const char *fName="liczby.txt";  //nazwa pliku
    while(m!=1){
        printf("\n\nWybierz jedna z ponizszych opcji:\n1.Stworz drzewo.\n2.Wyswietl drzewo.\n3.Dokonaj zamiany lewego poddrzewa z prawym poddrzewem.\n4.Informacje o autorze.\n5.Wyjdz.");
        scanf("%d",&k);
        switch(k){
            case 1:
                if(p==0){
                    printf("\nTworze drzewo BST...\n");
                    addFromFile(fName, &root);
                    p=1;
                }
                else{
                    printf("\nJuz stworzyles drzewo!\n");
                }
                break;
            case 2:
                if(p==1)
                {
                    elem=countNodes(root);
                    visual(root,elem);
                }
                else
                {
                     printf("\nNajpierw musisz stworzyc drzewo!\n");
                }
                break;
            case 3: if(p==1){
                        changeSubtree(&root,fName, temp);
                    }
                    else{
                        printf("\nNajpierw musisz stworzyc drzewo!\n");
                    }
                    break;
            case 4:
                printf("\nCezary Grabowski, grupa K5X2S1\n");
                break;
            case 5: m=1;
                    break;

            default: break;
            }
    }
    return 0;
}
