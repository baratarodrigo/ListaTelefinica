#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct contact
{
    char fname[15];
    char lname[15];
    char mobile_no[15];
    char tag[15];
};
typedef struct contact contact;

void add_contact()
{
    system("cls");
    FILE *fptr;
    contact cn;
    fptr = fopen("PhoneBook","a");

    printf("\n<Preencha campos>\n");

    printf("Primeiro Nome : ");
    scanf("%s", &cn.fname);

    printf("Apelido : ");
    scanf("%s", &cn.lname);

    printf("\nNumero de telefone : ");
    scanf("%s", &cn.mobile_no);

    printf("\nTag(ou nada) : ");
    scanf("%s", &cn.tag);

    fwrite(&cn, sizeof(contact), 1, fptr);

    fclose(fptr);

    printf("Pressione quaquer tecla.");
	getch();
    system("cls");
}

int directory_info(){
    FILE *fptr;

    fptr = fopen("PhoneBook", "r");
    fseek(fptr, 0, SEEK_END);

    return ftell(fptr)/sizeof(contact);
}

int tag_info(char tag[])
{
    int num = 0;
    FILE *fptr;
    contact cn;
    fptr = fopen("PhoneBook", "r");

    while(fread(&cn, sizeof(contact), 1, fptr))
    {
        if(strcmp(strlwr(cn.tag), strlwr(tag)) == 0)
            num++;
    }
    return num;
}


void display()
{
    system("cls");
    FILE *fptr;
    contact cn;
    int mode, count = 1, i, n;
    fptr = fopen("PhoneBook", "r");

    printf("1 : Ver a quanto tempo foi criado (ascendente)\n");
    printf("2 : Ver a quanto tempo foi criado (descendente)\n");
    printf("Choose Display Mode : ");
    scanf("%d", &mode);
    n = directory_info();
    printf("---------------------------------------------------------------------\n");
    printf("|Numero de contactos : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "Nome", "Apelido", "Numero", "Tag");
    printf("---------------------------------------------------------------------");

    if(mode == 1)
    {
        while(fread(&cn, sizeof(contact), 1, fptr))
        {
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
        }
    }

    else if (mode == 2)
    {
        fseek(fptr,-(sizeof(cn)), SEEK_END);

        for(i = 1; i <= n; ++i)
        {
            fread(&cn, sizeof(contact), 1, fptr);
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
            fseek(fptr, -2*sizeof(contact), SEEK_CUR);
        }
    }

    else
        printf("\n|Invalido !!!                                       |");

    printf("\n---------------------------------------------------------------------\n");

    fclose(fptr);

    printf("\n\nPressione quaquer tecla. : ");
	getch();
    system("cls");
}

void display_by_tag()
{
    system("cls");
    char tag[20];
    FILE *fptr;
    contact cn;
    int count=1, n;
    fptr = fopen("PhoneBook", "r");
    fflush(stdin);
    printf("Enter Tag : ");
    scanf("%s", tag);

    n = tag_info(tag);
    printf("---------------------------------------------------------------------\n");
    printf("|Numero de contactos : %2d                                      |\n", n);
    printf("---------------------------------------------------------------------");
    printf("\n|%-3s| %-15s%-15s%-20s%-12s|\n", "Sno", "Nome", "Apelido", "Numero", "Tag");
    printf("---------------------------------------------------------------------");

    while(fread(&cn, sizeof(contact), 1, fptr))
    {
        if(strcmp(strlwr(cn.tag), strlwr(tag)) == 0)
            printf("\n|%-3d| %-15s%-15s%-20s%-12s|", count++, cn.fname, cn.lname, cn.mobile_no, cn.tag);
    }

    printf("\n---------------------------------------------------------------------\n");

    fclose(fptr);
    fflush(stdin);
    printf("\n\nPressione quaquer tecla.: ");
	getch();
    system("cls");
}


void modify_contact()
{
    system("cls");
    FILE *fptr, *fptr1;
    contact cn;
    char fname[15];
    char lname[15];
    char modify;
    int found = 0;

    fptr = fopen("PhoneBook", "r");
    fptr1 = fopen("helper", "w");

    printf("Digite o Nome que quer editar:\n");
	printf("Enter First name: ");
	scanf("%s",&fname);
	printf("Digite o Apelido: ");
	scanf("%s",&lname);
	fflush(stdin);

	while(fread(&cn,sizeof(contact),1,fptr))
    {
        if(strcmp(strlwr(cn.fname),strlwr(fname))==0&&strcmp(strlwr(cn.lname),strlwr(lname))==0)
        {
            found = 1;
            printf("\nMudar o Nome?<y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if(modify == 'y' || modify == 'Y')
            {
                printf("Digite o novo Nome : ");
                scanf("%s", &cn.fname);
                fflush(stdin);
            }
            printf("\nMudar o Apelido?<y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if(modify == 'y' || modify == 'Y')
            {
                printf("Digite o novo Apelido : ");
                scanf("%s", &cn.lname);
                fflush(stdin);
            }
            printf("\nMudar o Numero? <y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if(modify == 'y' || modify == 'Y')
            {
                printf("Digite o novo Numero : ");
                scanf("%s", &cn.mobile_no);
                fflush(stdin);
            }
            printf("\nMudar a  Tag? <y/n> : ");
            scanf("%c", &modify);
            fflush(stdin);
            if(modify == 'y' || modify == 'Y')
            {
                printf("Digite a nova Tag : ");
                scanf("%s", &cn.tag);
                fflush(stdin);
            }
        }
        fwrite(&cn, sizeof(contact), 1, fptr1);
    }
    fclose(fptr);
    fclose(fptr1);

    if(found == 1)
    {
        fptr1 = fopen("helper", "r");
        fptr = fopen("PhoneBook", "w");

        while(fread(&cn, sizeof(contact), 1, fptr1))
            fwrite(&cn, sizeof(contact), 1, fptr);

        printf("\nContacto Mudado com sucesso\n");
    }
    else
        printf("Contacto nao encontrado");

    fclose(fptr);
    fclose(fptr1);

    printf("\n\nPressione quaquer tecla. : ");
	getch();
    system("cls");
}

void search_contact(){
	system("cls");
	FILE *fp;
	contact cn;
	int c,flag=0;
	fp=fopen("PhoneBook","r");
	if(fp==NULL){
		printf("\nErro ao abrir\n");
		exit(1);
	}
	printf("\n------------------------------------\n");
	printf("***Menu***\n");
	printf("----------------------------------------\n");
	printf("1. Pesquisar pelo Nome\n2. Pesquisar pelo Numero\n");
	printf("Escolha : ");
	scanf("%d",&c);
	fflush(stdin);
	if(c==1){
	char fname[30],lname[30];		
	printf("Digite o Nome:\n");
	printf("Enter first name : ");
	scanf("%s",&fname);
	printf("Digite o Apelido : ");
	scanf("%s",&lname);
	fflush(stdin);
	while(fread(&cn,sizeof(cn),1,fp)==1){
		
		if(strcmp(strlwr(cn.fname),strlwr(fname))==0&&strcmp(strlwr(cn.lname),strlwr(lname))==0){
			flag=1;
			printf("\nDetail information about %s\n",fname);
			printf("---------------------------------------------------------------------\n");
            printf("\n|%-15s%-15s%-20s%-12s|\n", "Nome", "Apelido", "Numero", "Tag");
            printf("---------------------------------------------------------------------");
            printf("\n|%-15s%-15s%-20s%-12s|\n",  cn.fname, cn.lname, cn.mobile_no, cn.tag);
			break;
			}
		}
		if(flag==0){
		printf("\nNao encontrado\n");
		fclose(fp);}
	}
	else if(c==2){
		char phone[10];
		printf("Digite o Numero: ");
		scanf("%s",&phone);
		while(fread(&cn,sizeof(cn),1,fp)==1){
			if(strcmp(phone,cn.mobile_no)==0){
				flag=1;
				printf("\n\nDetail information about %s",phone);
				printf("---------------------------------------------------------------------\n");
                printf("\n|%-15s%-15s%-20s%-12s|\n", "Nome", "Apelido", "Numero", "Tag");
                printf("---------------------------------------------------------------------");
                printf("\n|%-15s%-15s%-20s%-12s|\n",  cn.fname, cn.lname, cn.mobile_no, cn.tag);
			    break;
			}
		}
		if(flag==0) {
		printf("\nNao encontrado\n");
		fclose(fp);
		}
	}
	else{
		printf("Invalido!!");
		fclose(fp);
	}
	printf("Pressione quaquer tecla.:");
	getch();
	system("cls");
}


void delete_contact(){
	contact cn;
	FILE *fptr,*fptr1;
	int flag;
	system("cls");
	fptr=fopen("PhoneBook","r");
	if(fptr==NULL){
		printf("Nao adicionado ainda");
	}
	else{
		fptr1=fopen("helper","w+");
		if(fptr1==NULL)printf("Erro ao abrir");
		else{
			
			int choice;
			printf("\n----------------------------------------");
			printf("\n***Menu de Eliminação***\n");
			printf("----------------------------------------\n");
			printf("1.Eliminar pelo Numero\n2.Eliminar pelo Nome\n");
			printf("Enter your choice: ");
			scanf("%d",&choice);
			if(choice==1){
				char mobile_no[25];
				printf("Digite o Numero:");
				scanf("%s",&mobile_no);
				fflush(stdin);
				while(fread(&cn,sizeof(cn),1,fptr)==1){
					if(strcmp(mobile_no,cn.mobile_no)!=0){
						fwrite(&cn,sizeof(cn),1,fptr1);
					}
					if(strcmp(mobile_no,cn.mobile_no)==0){
						flag=1;
					}
				}
			}
			else if(choice==2){
			char fname[25],lname[25];
			printf("Digite o Nome: ");
			scanf("%s",&fname);
			printf("Digite o Apelido: ");
			scanf("%s",&lname);
			fflush(stdin);
			while(fread(&cn,sizeof(cn),1,fptr)==1){
				if(strcmp(strlwr(cn.fname),strlwr(fname))!=0||strcmp(strlwr(cn.lname),strlwr(lname))!=0){
					fwrite(&cn,sizeof(cn),1,fptr1);
				}
				if(strcmp(strlwr(cn.fname),strlwr(fname))==0&&strcmp(strlwr(cn.lname),strlwr(lname))==0){
					flag=1;
				}
			}
		}else{
			printf("\nInalido!\nPressione quaquer tecla.");
			getch();
			system("cls");
		}
		
			fclose(fptr);
			fclose(fptr1);
			if(flag!=1){
				printf("Nao ha contactos para eliminar!\n");
			}
			else{
				fptr1 = fopen("helper", "r");
				fptr = fopen("PhoneBook", "w");
				while(fread(&cn, sizeof(contact), 1, fptr1))
					fwrite(&cn, sizeof(contact), 1, fptr);
				printf("\nContacto eliminado com sucesso\n");
				
			}
			fclose(fptr1);
			fclose(fptr);
		}
	}
	printf("Pressione quaquer tecla:");
	getch();
	system("cls");
}


int main()
{
    int operation = 1;

    while(operation)
    {
        printf("\n1 : Criar Contacto\n");
        printf("2 : Mostrar Caminho\n");
        printf("3 : Mostrar pelas Tags\n");
        printf("4 : Editar Contactos\n");
        printf("5 : Pesquisar Contactos\n");
        printf("6 : Eliminar Contactos\n");
        printf("7 : Sair\n");
        printf("\nEscolha uma opçao : ");
        scanf("%d", &operation);

        switch(operation)
        {
            case 1 :
                add_contact();
                break;
            case 2 :
                display();
                break;
            case 3 :
                display_by_tag();
                break;
            case 4 :
                modify_contact();
                break;
            case 5:
            	search_contact();
            	break;
            case 6:
            	delete_contact();
            	break;
            case 7:
            	exit(1);
            	break;
            default:
            	system("cls");
            	printf("\nInvalido !!");
                printf("\nDigite entre 1 e 7");
                printf("\n Enter any key to continue");
                getch();
                system("cls");
        }
    }

    return 0;
}
