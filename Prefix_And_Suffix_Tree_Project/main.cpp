#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <windows.h>
struct node
{
    char *karakter;
    struct node * dal[40];
    int deger;
};
typedef struct node node;
int AGAC_OLUSTUR(node *agac,char *kelime,int benzerlik,int icicedal,int icicedal_Dizi[],char yedekle[],int deger[],int yedek_sayi);
void AGACI_GRAFIKTE_CIZ(node *agac,int Ust_Koordinat,int Yan_Koordinat,int alt,int renk);
int YAZDIR(node *iter,int ic);
int KELIME_UZUNLUGUNU_BUL(char kelime[]);
int DAL_BULUCU(node *agac,int toplam);
int EN_UZUN_DAL_BULUCU(node *agac,int toplam);
void KATARI_GRAFIKTE_CIZ(node *agac,int Ust_Koordinat,int Yan_Koordinat,int alt,int renk,int baslanandal);
int KATAR_GECIYORMU(node * agac,char Aranacak_Katar[],int benzerlik,int Aranacak_Katar_Uzunluk,int Ust_Koordinat,int Yan_Koordinat,int alt,int renk,int ilk,node *tut,int kacin_kaci);
int main()
{
    char *Ana_Cumle=(char*)malloc(sizeof(char)*200);
    char *kelime=(char*)malloc(sizeof(char)*200);
    char Son_Ek_Dizi[200][200];
    char On_Ek_Dizi[200][200];
    int Son_Ek_Sayisi=0;
    int On_Ek_Sayisi=0;
    int Ayni_Ek_Varmi=0;
    int kelime_uzunlugu;
    int uzunluk_kontrol;
    Ana_Cumle[0]='\0';
    kelime[0]='\0';
    node *agac;
    FILE *dosya;
    char *Dosya_Adi;
    Dosya_Adi=(char*)malloc(sizeof(char)*200);
    int secim=0;
    int agac_olustumu_kontrol=0;
    int kel=KELIME_UZUNLUGUNU_BUL(kelime);
    agac=(node*)malloc(sizeof(node));
    agac->karakter=(char*)malloc(sizeof(char)*200);
    int Ust_Koordinat=0;
    int Yan_Koordinat=0;
    char Aranacak_Katar[200];
    while(1)
    {
        printf("\n\t\t*******************  1 - Sonek Agaci Olusturulmasi Icin Kelime Alinacak Dosya Belirleme         *******************\n");
        printf("\n\t\t*******************  2 - Sonek Agaci Olusturulabilirmi ?                                        *******************\n");
        printf("\n\t\t*******************  3 - Sonek Agacini Grafikte Goster                                          *******************\n");
        printf("\n\t\t*******************  4 - Sonek Agani Duz Goster                                                 *******************\n");
        printf("\n\t\t*******************  5 - Sonek Agacindan Verilen P Katari Geciyormu ?                           *******************\n");
        printf("\n\t\t*******************  6 - En Uzun Alt Katar Nedir Ve Kac Kez Tekrar Etmektedir ?                 *******************\n");
        printf("\n\t\t*******************  7 - En Cok Tekrar Eden Alt Katar Nedir Ve Kac Kez Tekrar Etmektedir ?      *******************\n");
        printf("\n\t\t*******************  9 - Cikis                                                                  *******************\n");
        printf("\n\t\t*******************  Lutfen Seciminizi Giriniz : ");
        scanf("%d",&secim);
        printf("\n");
        if(secim==1)
        {
            printf("--> Dosya Adini Giriniz(.txt) : \n");
            scanf("%s",Dosya_Adi);
            if(dosya=fopen(Dosya_Adi,"r"))
            {
                fscanf(dosya,"%s",Ana_Cumle);
                fclose(dosya);
                printf("--> Dosyadan Kelime Alindi\n");
                printf("--> Alinan Kelime = %s\n\n",Ana_Cumle);
                kelime=Ana_Cumle;
                agac->dal[0]=(node*)malloc(sizeof(node));
                agac->dal[0]->karakter=(char*)malloc(sizeof(char)*200);
                kel=KELIME_UZUNLUGUNU_BUL(kelime);
                for(int k=0; k<kel; k++)
                {
                    agac->dal[0]->karakter[k]=kelime[k];
                }
                agac->dal[0]->karakter[kel]='\0';
                agac->dal[1]=NULL;
                agac->dal[0]->dal[0]=NULL;
                agac->dal[0]->deger=1;
                agac_olustumu_kontrol=0;
            }
            else
            {
                printf("--> Bu Isimle Kayitli Dosya Bulunamadi !!!\n\n");
                agac_olustumu_kontrol=0;
            }
        }
        else if(secim==2)
        {
            if(kelime[0]=='\0')
            {
                printf("--> Agac Yapilmasi Icin Ilk Olarak Kelime Dosyasini Giriniz \n\n");
                agac_olustumu_kontrol=0;
            }
            else
            {
                // Sonekleri Bul
                Son_Ek_Sayisi=0;
                while(kelime[Son_Ek_Sayisi]!='\0')
                {
                    int y=Son_Ek_Sayisi;
                    int k=0;
                    while(kelime[y]!='\0')
                    {
                        Son_Ek_Dizi[Son_Ek_Sayisi][k]=kelime[y];
                        y++;
                        k++;
                    }
                    Son_Ek_Dizi[Son_Ek_Sayisi][k]='\0';
                    Son_Ek_Sayisi++;
                }
                // Sonekleri Yazdir
                printf("--> Kelimenin Sonekleri : \n\n");
                for(int k=0; k<Son_Ek_Sayisi; k++)
                {
                    printf("\t %d : %s\n",k+1,Son_Ek_Dizi[k]);
                }
                // Onekleri Bul
                On_Ek_Sayisi=Son_Ek_Sayisi;
                for(int k=1; k<On_Ek_Sayisi+1; k++)
                {
                    for(int a=0; a<k; a++)
                    {
                        On_Ek_Dizi[k-1][a]=kelime[a];
                    }
                    On_Ek_Dizi[k-1][k]='\0';
                }
                // Onekleri Yazdir
                printf("\n--> Kelimenin Onekleri : \n\n");
                for(int k=0; k<On_Ek_Sayisi; k++)
                {
                    printf("\t %d : %s\n",k+1,On_Ek_Dizi[k]);
                }
                printf("\n");
                // AGAC OLUSURMU KONTROL
                Ayni_Ek_Varmi=0;
                for(int k=1; k<Son_Ek_Sayisi; k++)
                {
                    for(int a=0; a<Son_Ek_Sayisi-1; a++)
                    {
                        kelime_uzunlugu=KELIME_UZUNLUGUNU_BUL(kelime);
                        uzunluk_kontrol=0;
                        for(int d=0; d<kelime_uzunlugu-k+1; d++)
                        {
                            if(Son_Ek_Dizi[k][d]==On_Ek_Dizi[a][d])
                            {
                                uzunluk_kontrol++;
                            }
                        }
                        if(uzunluk_kontrol==kelime_uzunlugu-k+1)
                        {
                            Ayni_Ek_Varmi++;
                            printf("--> Sonek Ve Onek'te Ayni Ek Bulundu : Sonek %d -> %s , Onek %d -> %s \n",k+1,Son_Ek_Dizi[k],a+1,On_Ek_Dizi[a]);
                        }
                    }
                }
                printf("\n");
                if(Ayni_Ek_Varmi==0)
                {
                    kel=KELIME_UZUNLUGUNU_BUL(kelime);
                    for(int k=0; k<kel; k++)
                    {

                        kelime[k]=kelime[k+1];
                    }
                    kelime[kel]='\0';
                    // Agaci Olustur
                    int deger[1]= {1};
                    while(kelime[0]!='\0')
                    {
                        int yedek_sayi=0;
                        char yedekle[200];
                        int icicedal_Dizi[30]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                        int benzerlik=0;
                        int d=0;
                        int icicedal=0;
                        kel=KELIME_UZUNLUGUNU_BUL(kelime);
                        d=AGAC_OLUSTUR(agac,kelime,benzerlik,icicedal,icicedal_Dizi,yedekle,deger,yedek_sayi);
                        for(int k=0; k<kel; k++)
                        {
                            kelime[k]=kelime[k+1];
                        }
                        kelime[kel]='\0';
                    }
                    printf("--> Agac Olusturuldu\n\n");
                    agac_olustumu_kontrol=1;
                }
                else
                {
                    printf("--> Sonek Ve Onek'lerde Ortak Ek Bulundugu Icin Sonek Agaci Olusturulamaz!!!\n\n\n");
                    agac_olustumu_kontrol=0;
                }
            }
        }
        else if(secim==3)
        {
            if(agac_olustumu_kontrol==0)
            {
                printf("--> Ilk Once Agac Olusturun\n\n");
            }
            else if(agac_olustumu_kontrol==1)
            {
                Ust_Koordinat=650;
                Yan_Koordinat=65;
                int alt=180;
                int renk=2;
                initwindow(1300,650);
                setcolor(9);
                circle(650,35,30);
                delay(100);
                outtextxy(630,20,"Sonek");
                outtextxy(630,35,"Agaci");
                delay(100);
                AGACI_GRAFIKTE_CIZ(agac,Ust_Koordinat,Yan_Koordinat,alt,renk);
                getch();
                closegraph();
            }
        }
        else if(secim==4)
        {
            if(agac_olustumu_kontrol==0)
            {
                printf("--> Ilk Once Agac Olusturun\n\n");
            }
            else if(agac_olustumu_kontrol==1)
            {
                printf("\t\t\tSonek Agac Dallari : \n\n\n");
                int ic=0;
                int y;
                y=YAZDIR(agac,ic);
                printf("\n\n");
            }
        }
        else if(secim==5)
        {
            if(agac_olustumu_kontrol==0)
            {
                printf("--> Ilk Once Agac Olusturun\n\n");
            }
            else if(agac_olustumu_kontrol==1)
            {
                char cevirici[5];
                int kacin_kaci=-1;
                int benzerlik=0;
                int ilk=0;
                int d;
                int Aranacak_Katar_Uzunluk=0;
                printf("Sonek Agacinda Olup Olmadigini Aratmak Istediginiz Katari Yaziniz : ");
                scanf("%s",Aranacak_Katar);
                printf("\n");
                while(Aranacak_Katar[Aranacak_Katar_Uzunluk]!='\0')
                {
                    Aranacak_Katar_Uzunluk++;
                }
                Ust_Koordinat=650;
                Yan_Koordinat=65;
                int alt=180;
                int renk=2;
                initwindow(1300,650);
                setcolor(9);
                circle(650,35,30);
                delay(100);
                outtextxy(630,20,"Sonek");
                outtextxy(630,35,"Agaci");
                delay(100);
                node *tut=(node*)malloc(sizeof(node));
                d=KATAR_GECIYORMU(agac,Aranacak_Katar,benzerlik,Aranacak_Katar_Uzunluk,Ust_Koordinat,Yan_Koordinat,alt,renk,ilk,tut,kacin_kaci);
                sprintf(cevirici,"%d",d);
                setcolor(9);
                outtextxy(700,20,"Aratilan Katar : ");
                setcolor(6);
                outtextxy(800,20,Aranacak_Katar);
                setcolor(9);
                outtextxy(700,40,"Toplam = ");
                outtextxy(770,40,cevirici);
                outtextxy(700,60,"Kez Tekrar Ediyor");
                getch();
                closegraph();
                if(d==0)
                {
                    printf("\n--> Aratilan \"%s\" Katari Sonek Agacindan Gecmiyor\n\n",Aranacak_Katar);
                }
                else
                {
                    printf("\n--> Aratilan \"%s\" Katari %d Kez Tekrar Ediyor\n\n",Aranacak_Katar,d);
                }
            }

        }
        else if(secim==6)
        {
            if(agac_olustumu_kontrol==0)
            {
                printf("--> Ilk Once Agac Olusturun\n\n");
            }
            else if(agac_olustumu_kontrol==1)
            {
                char En_Uzun_Dal_Kelime[200][200];
                int En_Uzun_Dal_Sayisi[40];
                int Hangi_Dallar[40];
                int Dal_Tekrari_Sayisi[40];
                for(int a=0;a<40;a++)
                    {
                    En_Uzun_Dal_Sayisi[a]=0;
                    Hangi_Dallar[a]=-1;
                    Dal_Tekrari_Sayisi[a]=0;
                    }
                int tekrar_Ayni=0;
                int toplam=0;
                int toplam1=0;
                int d=0;
                while(agac->dal[d]!=NULL)
                {
                    toplam=EN_UZUN_DAL_BULUCU(agac->dal[d],0);
                    toplam1=DAL_BULUCU(agac->dal[d],0);
                    if(toplam>=En_Uzun_Dal_Sayisi[0])
                    {
                        if(toplam==En_Uzun_Dal_Sayisi[0])
                        {
                            if(toplam==0)
                            {
                                int k=0;
                                while(agac->dal[d]->karakter[k]!='\0')
                                {
                                    En_Uzun_Dal_Kelime[tekrar_Ayni][k]=agac->dal[d]->karakter[k];
                                    k++;
                                }
                                En_Uzun_Dal_Kelime[tekrar_Ayni][k]='\0';
                                En_Uzun_Dal_Sayisi[tekrar_Ayni]=toplam;//+1
                                Dal_Tekrari_Sayisi[tekrar_Ayni]=toplam1;
                                Hangi_Dallar[tekrar_Ayni]=d;
                                tekrar_Ayni++;
                            }
                            else
                            {
                                int k=0;
                                while(agac->dal[d]->karakter[k]!='\0')
                                {
                                    En_Uzun_Dal_Kelime[tekrar_Ayni][k]=agac->dal[d]->karakter[k];
                                    k++;
                                }
                                En_Uzun_Dal_Kelime[tekrar_Ayni][k]='\0';
                                En_Uzun_Dal_Sayisi[tekrar_Ayni]=toplam;
                                Dal_Tekrari_Sayisi[tekrar_Ayni]=toplam1;
                                Hangi_Dallar[tekrar_Ayni]=d;
                                tekrar_Ayni++;
                            }
                        }
                        else
                        {
                            tekrar_Ayni=0;
                            int k=0;
                            while(agac->dal[d]->karakter[k]!='\0')
                            {
                                En_Uzun_Dal_Kelime[tekrar_Ayni][k]=agac->dal[d]->karakter[k];
                                k++;
                            }
                            En_Uzun_Dal_Kelime[tekrar_Ayni][k]='\0';
                            En_Uzun_Dal_Sayisi[tekrar_Ayni]=toplam;//+1
                            Dal_Tekrari_Sayisi[tekrar_Ayni]=toplam1;
                            Hangi_Dallar[tekrar_Ayni]=d;
                            tekrar_Ayni++;
                        }
                    }
                    d++;
                }
                char cevirici[5];
                Ust_Koordinat=650;
                Yan_Koordinat=65;
                int alt=180;
                int renk=2;
                initwindow(1300,650);
                setcolor(9);
                circle(650,35,30);
                delay(100);
                outtextxy(630,20,"Sonek");
                outtextxy(630,35,"Agaci");
                delay(100);
                outtextxy(700,20,"En Uzun Alt Katar Yada Katarlar: ");
                for(int k=0; k<tekrar_Ayni; k++)
                {
                    KATARI_GRAFIKTE_CIZ(agac,Ust_Koordinat,Yan_Koordinat,alt,renk,Hangi_Dallar[k]);
                    setcolor(9);
                    setcolor((k+1)*2);
                    outtextxy(920,20+(20*k),En_Uzun_Dal_Kelime[k]);
                    sprintf(cevirici,"%d",Dal_Tekrari_Sayisi[0]);
                    setcolor(9);
                    outtextxy(700,40+(20*(tekrar_Ayni-1)),"Toplam = ");
                    outtextxy(765+(k*20),40+(20*(tekrar_Ayni-1)),cevirici);
                    if(k>0)
                        {
                        outtextxy(765+(k*10),40+(20*(tekrar_Ayni-1))," , ");
                        }
                    outtextxy(700,60+(20*(tekrar_Ayni-1)),"Kez Tekrar Ediyor");
                    printf("--> En Uzun Alt Katar %s 'dir Ve %d Kez Tekrar Etmektedir \n\n\n",En_Uzun_Dal_Kelime[k],Dal_Tekrari_Sayisi[k]);
                }
                getch();
                closegraph();
            }
        }
        else if(secim==7)
        {
            if(agac_olustumu_kontrol==0)
            {
                printf("--> Ilk Once Agac Olusturun\n\n");
            }
            else if(agac_olustumu_kontrol==1)
            {
                char En_Cok_Tekrar_Eden_Dal_Kelime[200][200];
                int En_Cok_Tekrar_Eden_Dal_Sayisi[40];
                int Hangi_Dallar[40];
                for(int a=0;a<40;a++)
                    {
                    En_Cok_Tekrar_Eden_Dal_Sayisi[a]=0;
                    Hangi_Dallar[a]=-1;
                    }
                int tekrar_Ayni=0;
                int toplam=0;
                int d=0;
                while(agac->dal[d]!=NULL)
                {
                    toplam=DAL_BULUCU(agac->dal[d],0);
                    if(toplam>=En_Cok_Tekrar_Eden_Dal_Sayisi[0])
                    {
                        if(toplam==En_Cok_Tekrar_Eden_Dal_Sayisi[0])
                        {
                            if(toplam==0)
                            {
                                int k=0;
                                while(agac->dal[d]->karakter[k]!='\0')
                                {
                                    En_Cok_Tekrar_Eden_Dal_Kelime[tekrar_Ayni][k]=agac->dal[d]->karakter[k];
                                    k++;
                                }
                                En_Cok_Tekrar_Eden_Dal_Kelime[tekrar_Ayni][k]='\0';
                                En_Cok_Tekrar_Eden_Dal_Sayisi[tekrar_Ayni]=toplam+1;
                                Hangi_Dallar[tekrar_Ayni]=d;
                                tekrar_Ayni++;
                            }
                            else
                            {
                                int k=0;
                                while(agac->dal[d]->karakter[k]!='\0')
                                {
                                    En_Cok_Tekrar_Eden_Dal_Kelime[tekrar_Ayni][k]=agac->dal[d]->karakter[k];
                                    k++;
                                }
                                En_Cok_Tekrar_Eden_Dal_Kelime[tekrar_Ayni][k]='\0';
                                En_Cok_Tekrar_Eden_Dal_Sayisi[tekrar_Ayni]=toplam;
                                Hangi_Dallar[tekrar_Ayni]=d;
                                tekrar_Ayni++;
                            }
                        }
                        else
                        {
                            tekrar_Ayni=0;
                            int k=0;
                            while(agac->dal[d]->karakter[k]!='\0')
                            {
                                En_Cok_Tekrar_Eden_Dal_Kelime[tekrar_Ayni][k]=agac->dal[d]->karakter[k];
                                k++;
                            }
                            En_Cok_Tekrar_Eden_Dal_Kelime[tekrar_Ayni][k]='\0';
                            En_Cok_Tekrar_Eden_Dal_Sayisi[tekrar_Ayni]=toplam;
                            Hangi_Dallar[tekrar_Ayni]=d;
                            tekrar_Ayni++;
                        }
                    }
                    d++;
                }
                char cevirici[5];
                Ust_Koordinat=650;
                Yan_Koordinat=65;
                int alt=180;
                int renk=2;
                initwindow(1300,650);
                setcolor(9);
                circle(650,35,30);
                delay(100);
                outtextxy(630,20,"Sonek");
                outtextxy(630,35,"Agaci");
                delay(100);
                outtextxy(700,20,"En Cok Tekrar Eden Katar Yada Katarlar: ");
                for(int k=0; k<tekrar_Ayni; k++)
                {
                    KATARI_GRAFIKTE_CIZ(agac,Ust_Koordinat,Yan_Koordinat,alt,renk,Hangi_Dallar[k]);
                    setcolor(9);
                    setcolor((k+1)*2);
                    outtextxy(970,20+(20*k),En_Cok_Tekrar_Eden_Dal_Kelime[k]);
                    printf("--> En Cok Tekrar Eden Alt Katar %s 'dir Ve %d Kez Tekrar Etmektedir \n\n\n",En_Cok_Tekrar_Eden_Dal_Kelime[k],En_Cok_Tekrar_Eden_Dal_Sayisi[k]);
                }
                sprintf(cevirici,"%d",En_Cok_Tekrar_Eden_Dal_Sayisi[0]);
                setcolor(9);
                outtextxy(700,40+(20*(tekrar_Ayni-1)),"Toplam = ");
                outtextxy(765,40+(20*(tekrar_Ayni-1)),cevirici);
                outtextxy(700,60+(20*(tekrar_Ayni-1)),"Kez Tekrar Ediyor");
                getch();
                closegraph();
            }
        }
        else if(secim==9)
        {
            break;
        }
    }
    return 0;
}
int AGAC_OLUSTUR(node *agac,char *kelime,int benzerlik,int icicedal,int icicedal_Dizi[],char yedekle[],int deger[],int yedek_sayi)
{
    int kelimeuzunlugu;
    char tut[200];// KARAKTER YERI DEGISTIRIRKEN KAYBOLMASIN DIYE ATANAN DIZI
    int kontrol=0;// alt dallar eklenmediysa 1.dallarin sonuna ekleme icin
    int u1=0;//DUR
    node * nodetut=(node*)malloc(sizeof(node));
    node * iter=(node*)malloc(sizeof(node));
    iter->karakter=(char*)malloc(sizeof(char)*200);
    iter=agac;
    while(iter->dal[u1]!=NULL)// 1.DALDA ILERLEME
    {
        if(icicedal==0)
        {
            if(iter->dal[u1]->karakter[0]==kelime[benzerlik])// 1.DALDAN ARANAN KELIMEYLE BENZERLIK VAR// 0 0
            {
                int dal_b1=0;
                // Hemen daldaki veriyi yedekle
                kelimeuzunlugu=KELIME_UZUNLUGUNU_BUL(iter->dal[u1]->karakter);
                for(int k=0; k<kelimeuzunlugu; k++)
                {
                    yedekle[k]=iter->dal[u1]->karakter[k];
                }
                yedekle[kelimeuzunlugu]='\0';
                yedek_sayi=iter->dal[u1]->deger;
                dal_b1++;
                benzerlik++;
                while(iter->dal[u1]->karakter[dal_b1]==kelime[benzerlik])// KAC HARF BENZER OLCER
                {
                    dal_b1++;
                    benzerlik++;
                }
                if(icicedal==0)
                {
                    icicedal_Dizi[icicedal]=benzerlik;
                    icicedal++;
                }
                else
                {
                    int top=0;
                    for(int k=0; k<icicedal; k++)
                    {
                        top+=icicedal_Dizi[k];
                    }
                    icicedal_Dizi[icicedal]=benzerlik-top;
                    icicedal++;
                }
                if(benzerlik<kelimeuzunlugu)// dal zaten varken daha kisa benzer kelime girerse
                    {
                    if(iter->dal[u1]->dal[0]!=NULL)
                        {
                            nodetut->karakter=(char*)malloc(sizeof(char)*200);
                            for(int k=0;k<benzerlik;k++)
                                {
                                nodetut->karakter[k]=iter->dal[u1]->karakter[k];
                                }
                            nodetut->karakter[benzerlik]='\0';
                            int p=0;
                            while(iter->dal[u1]->karakter[p]!='\0')
                                {
                                    iter->dal[u1]->karakter[p]=iter->dal[u1]->karakter[p+benzerlik];
                                p++;
                                }
                                iter->dal[u1]->karakter[p]='\0';
                        nodetut->dal[0]=iter->dal[u1];
                        nodetut->dal[1]=(node*)malloc(sizeof(node));
                        nodetut->dal[1]->karakter=(char*)malloc(sizeof(char)*200);
                        deger[0]++;
                        nodetut->dal[1]->deger=deger[0];
                        kelimeuzunlugu=KELIME_UZUNLUGUNU_BUL(kelime);
                        for(int k=0;k<kelimeuzunlugu;k++)
                            {
                                if(k+benzerlik<=kelimeuzunlugu)
                                    {
                                    nodetut->dal[1]->karakter[k]=kelime[k+benzerlik];
                                    }
                            }
                        nodetut->dal[1]->karakter[kelimeuzunlugu]='\0';
                        nodetut->dal[1]->dal[0]=NULL;
                        nodetut->dal[2]=NULL;
                        iter->dal[u1]=nodetut;
                        return 1;
                        }
                    }
                kontrol=AGAC_OLUSTUR(iter->dal[u1],kelime,benzerlik,icicedal,icicedal_Dizi,yedekle,deger,yedek_sayi);
                if(kontrol==1)
                {
                    return 1;
                }
                else if(kontrol==2)
                {
                    for(int k=0; k<icicedal_Dizi[icicedal-1]; k++)
                    {
                        iter->dal[u1]->karakter[k]=yedekle[k];
                    }
                    iter->dal[u1]->karakter[icicedal_Dizi[icicedal-1]]='\0';
                    iter->dal[u1]->deger=0;
                    return 1;
                }
            }
        }
        else
        {
            if(iter->dal[u1]->karakter[0]==kelime[benzerlik])// 1.DALDAN ARANAN KELIMEYLE BENZERLIK VAR// 0 0
            {
                int dal_b=0;
                // Hemen daldaki veriyi yedekle
                kelimeuzunlugu=KELIME_UZUNLUGUNU_BUL(iter->dal[u1]->karakter);
                for(int k=0; k<kelimeuzunlugu; k++)
                {
                    yedekle[k]=iter->dal[u1]->karakter[k];
                }
                yedekle[kelimeuzunlugu]='\0';
                yedek_sayi=iter->dal[u1]->deger;
                benzerlik++;
                dal_b++;
                while(iter->dal[u1]->karakter[dal_b]==kelime[benzerlik])// KAC HARF BENZER OLCER
                {
                    dal_b++;
                    benzerlik++;
                }
                int top=0;
                for(int k=0; k<icicedal; k++)
                {
                    top+=icicedal_Dizi[k];
                }
                icicedal_Dizi[icicedal]=benzerlik-top;
                icicedal++;
                kontrol=AGAC_OLUSTUR(iter->dal[u1],kelime,benzerlik,icicedal,icicedal_Dizi,yedekle,deger,yedek_sayi);
                if(kontrol==1)
                {
                    return 1;
                }
                else if(kontrol==2)
                {
                    for(int k=0; k<icicedal_Dizi[icicedal-1]; k++)
                    {
                        iter->dal[u1]->karakter[k]=yedekle[k];
                    }
                    iter->dal[u1]->karakter[icicedal_Dizi[icicedal-1]]='\0';
                    iter->dal[u1]->deger=0;
                    return 1;
                }
            }
        }
        u1++;
    }
    if(kontrol==0) // EN SON YADA EN ALTA EKLEME
    {
        int a=0;
        if(icicedal==0)
        {
            while(iter->dal[a]!=NULL)
            {
                a++;
            }
            iter->dal[a]=(node*)malloc(sizeof(node));
            iter->dal[a]->karakter=(char*)malloc(sizeof(char)*200);
            iter->dal[a]->dal[0]=NULL;
            iter->dal[a+1]=NULL;
            deger[0]++;
            iter->dal[a]->deger=deger[0];
            kelimeuzunlugu=KELIME_UZUNLUGUNU_BUL(kelime);
            for(int yaz=0; yaz<kelimeuzunlugu; yaz++)
            {
                iter->dal[a]->karakter[yaz]=kelime[yaz];
            }
            iter->dal[a]->karakter[kelimeuzunlugu]='\0';
            return 1;
        }
        else
        {
            if(iter->dal[0]==NULL)
            {
                //DAL ACILIYOR
                iter->dal[0]=(node*)malloc(sizeof(node));
                iter->dal[0]->karakter=(char*)malloc(sizeof(char)*200);
                iter->dal[0]->dal[0]=NULL;
                iter->dal[0]->deger=yedek_sayi;
                iter->dal[1]=NULL;
                // 1.DALDAN KALAN KELIMEYI 1.DALIN 0.DALINA YAZ
                int q=0;
                while(yedekle[q]!='\0')
                {
                    iter->dal[0]->karakter[q]=yedekle[q+icicedal_Dizi[icicedal-1]];
                    q++;
                }
                iter->dal[0]->karakter[q]='\0';
                // 2.DALLARA YENI DALI YAZ
                //
                iter->dal[1]=(node*)malloc(sizeof(node));
                iter->dal[1]->karakter=(char*)malloc(sizeof(char)*200);
                iter->dal[1]->dal[0]=NULL;
                iter->dal[2]=NULL;
                deger[0]++;
                iter->dal[1]->deger=deger[0];
                kelimeuzunlugu=KELIME_UZUNLUGUNU_BUL(kelime);

                for(int yaz=0; yaz<kelimeuzunlugu; yaz++)
                {
                    iter->dal[1]->karakter[yaz]=kelime[yaz+benzerlik];
                }
                iter->dal[1]->karakter[kelimeuzunlugu]='\0';
                return 2;
            }
            else
            {
                int b=0;
                while(iter->dal[b]!=NULL)
                {
                    b++;
                }
                iter->dal[b]=(node*)malloc(sizeof(node));
                iter->dal[b]->karakter=(char*)malloc(sizeof(char)*200);
                iter->dal[b]->dal[0]=NULL;
                iter->dal[b+1]=NULL;
                deger[0]++;
                iter->dal[b]->deger=deger[0];
                kelimeuzunlugu=KELIME_UZUNLUGUNU_BUL(kelime);
                for(int yaz=0; yaz<kelimeuzunlugu; yaz++)
                {
                    iter->dal[b]->karakter[yaz]=kelime[yaz+benzerlik];
                }
                iter->dal[b]->karakter[kelimeuzunlugu]='\0';
                return 2;
            }
        }
    }
}
void AGACI_GRAFIKTE_CIZ(node *agac,int Ust_Koordinat,int Yan_Koordinat,int alt,int renk)
{
    node *iter=(node*)malloc(sizeof(node));
    iter=agac;
    char cevirici[4];
    int a1=0;
    while(iter->dal[a1]!=NULL)
    {
        setcolor(renk);
        if(a1%2==0)
        {
            sprintf(cevirici,"%d",agac->dal[a1]->deger);
            line(Ust_Koordinat,Yan_Koordinat,Ust_Koordinat+(-(a1/2)*alt),Yan_Koordinat+60+(a1/2*30));
            delay(200);
            circle(Ust_Koordinat+(-(a1/2)*alt),Yan_Koordinat+60+30+(a1/2*30),30);
            if(cevirici[0]!='0')
            {
                outtextxy(10+Ust_Koordinat+(-(a1/2)*alt)-20,Yan_Koordinat+60+10+(a1/2*30),cevirici);
            }
            outtextxy(Ust_Koordinat+(-(a1/2)*alt)-20,Yan_Koordinat+60+30+(a1/2*30),iter->dal[a1]->karakter);
            delay(200);
        }
        else
        {
            sprintf(cevirici,"%d",agac->dal[a1]->deger);
            line(Ust_Koordinat,Yan_Koordinat,Ust_Koordinat+((a1+1)/2)*alt,Yan_Koordinat+60+((a1+1)/2*30));
            delay(100);
            circle(Ust_Koordinat+((a1+1)/2)*alt,Yan_Koordinat+60+30+((a1+1)/2*30),30);
            if(cevirici[0]!='0')
            {
                outtextxy(10+Ust_Koordinat+((a1+1)/2)*alt-20,Yan_Koordinat+60+10+((a1+1)/2*30),cevirici);
            }
            outtextxy(Ust_Koordinat+((a1+1)/2)*alt-20,Yan_Koordinat+60+30+((a1+1)/2*30),iter->dal[a1]->karakter);
            delay(100);
        }
        if(iter->dal[a1]->dal[0]!=NULL)
        {
            if(a1%2==0)
            {
                AGACI_GRAFIKTE_CIZ(iter->dal[a1],Ust_Koordinat+(-(a1/2)*alt),Yan_Koordinat+60+60+(a1/2*30),alt-45,renk+2);
            }
            else
            {
                AGACI_GRAFIKTE_CIZ(iter->dal[a1],Ust_Koordinat+((a1+1)/2)*alt,Yan_Koordinat+60+60+((a1+1)/2*30),alt-45,renk+2);
            }
        }
        a1++;
    }
}
int YAZDIR(node *iter,int ic)
{
    int a=0;
    while(iter->dal[a]!=NULL)
    {
        for(int k=0; k<ic; k++)
        {
            printf("-->  ");
        }
        printf("--> = %s \n",iter->dal[a]->karakter);
        if(iter->dal[a]->dal[0]!=NULL)
        {
            ic++;
            YAZDIR(iter->dal[a],ic);
            ic--;
        }
        a++;
    }
    return 1;
}
int KELIME_UZUNLUGUNU_BUL(char kelime[])
{
    int kelimeuzunlugu=0;
    while(kelime[kelimeuzunlugu]!='\0')
    {
        kelimeuzunlugu++;
    }
    return kelimeuzunlugu;
}
int DAL_BULUCU(node *agac,int toplam)
{
    node *iter=(node*)malloc(sizeof(node));
    iter=agac;
    int u1=0;
    while(iter->dal[u1]!=NULL)
    {
        toplam++;
        if(iter->dal[u1]->dal[0]!=NULL)
        {
            toplam--;
            toplam=DAL_BULUCU(iter->dal[u1],toplam);
        }
        u1++;
    }
    return toplam;
}
int EN_UZUN_DAL_BULUCU(node *agac,int toplam)
{
    node *iter=(node*)malloc(sizeof(node));
    iter=agac;
    int u1=0;
    while(iter->dal[u1]!=NULL)
    {
        toplam++;
        int a=0;
        while(iter->dal[u1]->dal[a]!=NULL)
        {
            toplam=EN_UZUN_DAL_BULUCU(iter->dal[u1],toplam);
            a++;
        }
        u1++;
    }
    return toplam;
}
void KATARI_GRAFIKTE_CIZ(node *agac,int Ust_Koordinat,int Yan_Koordinat,int alt,int renk,int baslanandal)
{
    node *iter=(node*)malloc(sizeof(node));
    iter=agac;
    char cevirici[4];
    int a1=0;
    while(iter->dal[a1]!=NULL)
    {
        if(a1==baslanandal)
        {
            setcolor(renk);
            if(a1%2==0)
            {
                sprintf(cevirici,"%d",agac->dal[a1]->deger);
                line(Ust_Koordinat,Yan_Koordinat,Ust_Koordinat+(-(a1/2)*alt),Yan_Koordinat+60+(a1/2*30));
                delay(200);
                circle(Ust_Koordinat+(-(a1/2)*alt),Yan_Koordinat+60+30+(a1/2*30),30);
                if(cevirici[0]!='0')
                {
                    outtextxy(10+Ust_Koordinat+(-(a1/2)*alt)-20,Yan_Koordinat+60+10+(a1/2*30),cevirici);
                }
                outtextxy(Ust_Koordinat+(-(a1/2)*alt)-20,Yan_Koordinat+60+30+(a1/2*30),iter->dal[a1]->karakter);
                delay(200);
            }
            else
            {
                sprintf(cevirici,"%d",agac->dal[a1]->deger);
                line(Ust_Koordinat,Yan_Koordinat,Ust_Koordinat+((a1+1)/2)*alt,Yan_Koordinat+60+((a1+1)/2*30));
                delay(100);
                circle(Ust_Koordinat+((a1+1)/2)*alt,Yan_Koordinat+60+30+((a1+1)/2*30),30);
                if(cevirici[0]!='0')
                {
                    outtextxy(10+Ust_Koordinat+((a1+1)/2)*alt-20,Yan_Koordinat+60+10+((a1+1)/2*30),cevirici);
                }
                outtextxy(Ust_Koordinat+((a1+1)/2)*alt-20,Yan_Koordinat+60+30+((a1+1)/2*30),iter->dal[a1]->karakter);
                delay(100);
            }
            if(iter->dal[a1]->dal[0]!=NULL)
            {
                if(a1%2==0)
                {
                    AGACI_GRAFIKTE_CIZ(iter->dal[a1],Ust_Koordinat+(-(a1/2)*alt),Yan_Koordinat+60+60+(a1/2*30),alt-45,renk+2);
                }
                else
                {
                    AGACI_GRAFIKTE_CIZ(iter->dal[a1],Ust_Koordinat+((a1+1)/2)*alt,Yan_Koordinat+60+60+((a1+1)/2*30),alt-45,renk+2);
                }
            }
        }
        a1++;
    }
}
int KATAR_GECIYORMU(node * agac,char Aranacak_Katar[],int benzerlik,int Aranacak_Katar_Uzunluk,int Ust_Koordinat,int Yan_Koordinat,int alt,int renk,int ilk,node *tut,int kacin_kaci)
{
    node *iter=(node*)malloc(sizeof(node));
    iter=agac;
    int u1=0;
    int a=0;
    int kontrol=0;
    while(iter->dal[u1]!=NULL)
    {
        if(iter->dal[u1]->karakter[a]==Aranacak_Katar[benzerlik])
        {
            ilk++;
            if(ilk==1)
            {
                kacin_kaci=u1;
                tut=iter;
            }
            int kelime_uzunlugu=KELIME_UZUNLUGUNU_BUL(iter->dal[u1]->karakter);
            a++;
            benzerlik++;
            if(benzerlik==Aranacak_Katar_Uzunluk)
            {
                KATARI_GRAFIKTE_CIZ(tut,Ust_Koordinat,Yan_Koordinat,alt,renk,kacin_kaci);
                kontrol=DAL_BULUCU(iter->dal[u1],0);
                if(kontrol==0)
                {
                    return 1;
                }
                else
                {
                    return kontrol;
                }
            }
            if(iter->dal[u1]->karakter[a]=='\0')
            {
                int b=0;
                b=KATAR_GECIYORMU(iter->dal[u1],Aranacak_Katar,benzerlik,Aranacak_Katar_Uzunluk,Ust_Koordinat,Yan_Koordinat,alt,renk,ilk,tut,kacin_kaci);
                return b;
            }
            while(iter->dal[u1]->karakter[a]==Aranacak_Katar[benzerlik])
            {
                a++;
                benzerlik++;
                if(benzerlik==Aranacak_Katar_Uzunluk)
                {
                    KATARI_GRAFIKTE_CIZ(tut,Ust_Koordinat,Yan_Koordinat,alt,renk,kacin_kaci);
                    kontrol=DAL_BULUCU(iter->dal[u1],0);
                    if(kontrol==0)
                    {
                        return 1;
                    }
                    else
                    {
                        return kontrol;
                    }
                }
                if(kelime_uzunlugu<=a)
                {
                    int b=0;
                    b=KATAR_GECIYORMU(iter->dal[u1],Aranacak_Katar,benzerlik,Aranacak_Katar_Uzunluk,Ust_Koordinat,Yan_Koordinat,alt,renk,ilk,tut,kacin_kaci);
                    return b;
                }
            }
            if(benzerlik==kelime_uzunlugu)
            {
                int k=0;
                k=KATAR_GECIYORMU(iter->dal[u1],Aranacak_Katar,benzerlik,Aranacak_Katar_Uzunluk,Ust_Koordinat,Yan_Koordinat,alt,renk,ilk,tut,kacin_kaci);
                return k;
            }
        }
        u1++;
    }
    return 0;
}
