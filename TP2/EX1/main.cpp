/*
LAUB10038406
LAURENCE, BRUNO
C++
H13_TP2_EX1
30/03/13
Ce programme va lire 3 fichiers pour
en faire des listes chainées afin
d'effectuer 2 sorties sous forme de
fichier texte
*/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "facture.hpp"
#include <stdlib.h> //qsort

using namespace std;
//declaration des structures
typedef struct achat achat;
struct achat{
  struct achat *next;

  int    numeroProduit;
  int    quantite;
};
typedef struct commande commande;
struct commande{
  struct commande *next;

  int    numeroVendeur;
  int    numeroClient;
  struct achat *achats;
};
struct produit{
  struct produit * next;

  int    numeroProduit;
  char   Description[25];
  double PrixUnitaire;
  int    Quantite;
  int    Vendu;
};

struct client {
  struct client *next;

  int    numeroClient;
  double escompte;
};

// Liste chainee des clients
struct client * clients = NULL;
// Liste_chainee des produits
struct produit *produits = NULL;
// liste chainee des commandes
struct commande *commandes = NULL;


//structure tampon pour les recherches
struct trucachercher {
	struct trucachercher * next;
	int    truc;
};
//prototype
void *recherche(trucachercher * liste, int test);
//servira à localiser les élements voulu
void *recherche(trucachercher * liste, int test) {
	trucachercher *p;
	for (p = liste;p;p=p->next)
	{
		if (p->truc > test) return (0);
		if (p->truc == test) break;//si on trouve l'element on sort
	}
	return p; // et on retourne l'element
}

//initialisation des commandes
int init_Commandes()
{
	// on ouvre le fichier en lecture
	ifstream fichier("COMMANDES.DON", ios::in);

	if(!fichier)  // si l'ouverture echoue
	{
		cerr << "Impossible d'ouvrir le fichier COMMANDES.DON !" << endl;
		// on indique qu'une erreur s'est produite
		return (1);
	}

cerr << "ouverture du fichier COMMANDES.DON reussie" << endl;

	// on s'assure de la lecture en decimal
	fichier.setf(ios::dec, ios::basefield);

	// on selectionne la liste des commandes (element factice)
	struct commande *commandesuivante = (struct commande *) &commandes;

	// variable Sentinelle/Temporaire servant a  detecter les fins de listes
	int Sentinelle;

	// tant qu'il y'a une entree dans le fichier
	while(fichier >> Sentinelle)
	{
		// on cree une nouvelle commande
		commandesuivante->next = new commande;
		commandesuivante = commandesuivante->next;
		commandesuivante->next = NULL;

		// on remplis les champs:
		// le numero de Vendeur est deja  lu dans Sentinelle
		commandesuivante->numeroVendeur = Sentinelle;
		// le champs suivant est le nÂ° de Client
		fichier >> commandesuivante->numeroClient;

cerr << "nouvelle vente du vendeur numero" << commandesuivante->numeroVendeur << " pour le client " << commandesuivante->numeroClient << endl;

		// on cree la liste des achats (aucun element initial)
		achat *achatsuivant = (achat *) &commandesuivante->achats;

		// tant qu'on a pas de zero, ou une fin de fichier
		while ((fichier >> Sentinelle) && Sentinelle)
		{
			// on cree un nouvel achat
			achatsuivant->next = new achat;
			achatsuivant = achatsuivant->next;
			achatsuivant->next = NULL;

			// on remlit les champs
			// Le Numero de Produit est deja lu dans Sentinelle
			achatsuivant->numeroProduit = Sentinelle;
			// le champs suivant est la quantite
			fichier >> achatsuivant->quantite;

			// on pointe sur l'emplacement du prochain achat potentiel
			achatsuivant = (achat *) &achatsuivant->next;
		};
		fichier >> Sentinelle; // on lit le zero
		// on peut alors pointer sur l'emplacement de la prochaine commande potentielle
		commandesuivante = (commande *) &commandesuivante->next;
	}
	// on ferme le fichier
	fichier.close();

	// on indique que tout s'est bien passe
cerr << "fermeture du fichier COMMANDES.DON reussie" << endl;
	return (0);
}

int init_Produits()
{
	// on ouvre le fichier en lecture
	ifstream fichier("PRODUITS.DON", ios::in);

	if(!fichier)  // si l'ouverture echoue
	{
		cerr << "Impossible d'ouvrir le fichier " << "PRODUITS.DON" << " !" << endl;
		return 1;
	}

cerr << "Ouverture du fichier PRODUITS.DON reussie" << endl;

	// on s'assure de la lecture en decimal
	fichier.setf(ios::dec, ios::basefield);
	//en sans espaces
	fichier.setf(ios::skipws, ios::basefield);

	// on selectionne la liste des produits (element factice)
	struct produit *produitsuivant = (struct produit *) &produits;

	int NumProduit; // variable temporaire pour detecter les fins de listes
	int count = 0; //compte le nombre de produits differents

	// tant qu'il y'a une entree dans le fichier
	while(fichier >> NumProduit>> std::ws)
	{
		count++;

		// on cree une nouveau produit
		produitsuivant->next = new produit;
		produitsuivant = produitsuivant->next;
		produitsuivant->next = NULL;

		// on remplis les champs (le Numero de produit est deja  lu)
		produitsuivant->numeroProduit = NumProduit;
		// Aucune vente pour l'instant
		produitsuivant->Vendu = 0;

        // comme defini dans l'enonce, 25 char
		fichier.read(produitsuivant->Description,25);
		// le prix puis le produit se suivent
		fichier >> produitsuivant->PrixUnitaire >> produitsuivant->Quantite;


		produitsuivant = (produit *) &produitsuivant->next;
	}

	fichier.close();

cerr << "fermeture du fichier PRODUITS.DON reussie." << produits <<endl;

	return count;
}

int init_Clients()
{
	// on ouvre le fichier en lecture
	ifstream fichier("CLIENTS.DON", ios::in);

	if(!fichier)  // si l'ouverture echoue
	{
		cerr << "Impossible d'ouvrir le fichier CLIENTS.DON" << endl;
		return 1;
	}

cerr << "Ouverture du fichier CLIENTS.DON reussie" << endl;

	// on s'assure de la lecture en decimal
	fichier.setf(ios::dec, ios::basefield);
	//sans espace
	fichier.setf(ios::skipws, ios::basefield);

	// on selectionne la liste des clients
	struct client *clientsuivant = (struct client *) &clients;

	int NumClient;
	while(fichier >> NumClient >> std::ws)
	{
		// on cree une nouveau client
		clientsuivant->next = new client;
		clientsuivant = clientsuivant->next;
		clientsuivant->next = NULL;

		clientsuivant->numeroClient = NumClient;
		fichier >> clientsuivant->escompte;

cerr << "Nouveau client N° " << clientsuivant->numeroClient << " escompte : " << clientsuivant->escompte << endl;

		clientsuivant = (client *) &clientsuivant->next;
	}
	fichier.close();

	return 0;
}
// equivalent à strcmp, sera utiliser par qsort pour le tri
int compare(const void * a, const void * b){
  string s1= (*(produit **)a)->Description;
  string s2= (*(produit **)b)->Description;
  return (s1>s2?1:(s1==s2?0:-1));
}


int main(){
    /***************test client*******************/
        if (init_Clients())
	    cerr << "Echec de la procedure ";
        else
            cerr << "Init clients reussie ";
	cerr << clients << endl;
	/*************test commande*******************/
	if (init_Commandes()) cerr << "Echec de la proczdure " << commandes << endl;
	else
	    cerr << "Init commandes reussie " << commandes << endl;

/***************** test produits *******************/
	int count=init_Produits();
	if (count==0)
	{
		cerr << "Erreur lors de la creation de la liste des produits." << endl;
		return -1;
	}
	cerr << "Creation de la liste des produits reussie." << produits <<endl;


/**************SORTIE 1***************************************/
	FILE * pFile;
    pFile = fopen ("SORTIE_1.txt","w");
        if(pFile){
    cout << "Creation de la SORTIE_1.txt" << endl;}
    // pour chaque commande et tant qu'il y'a des commandes
	for (commande *co = commandes; co; co=co->next)
	{
		// on recupere le numero du client et de vendeur
		client *cl = (client *)recherche((trucachercher *)clients, co->numeroClient);
		//ecriture dans le fichier
		fprintf(pFile, Entete_Facture, co->numeroClient, co->numeroVendeur);

        /****calcul***/
		double SOUSTOTAL=0;
		// pour tous les achats
		for (achat *ac = co->achats; ac; ac=ac->next)
		{//on recherche le numero de produit fournit
			produit *pr = (produit *)recherche((trucachercher *)produits, ac->numeroProduit);
			if (!pr)
			{// si le produit n'existe pas on le signal NI et on l'affiche dans le fichier
				fprintf(pFile,"║      %03d                                                          NI         ║\n", ac->numeroProduit );
				continue;
			}
			string tag = "";
			int Quantite_livree = 0;
			//calcul du prix des produits
			pr->Vendu =pr->Vendu + ac->quantite;

			if (pr->Quantite <= 0)
			{//si la quantité n'est plus disponible en stock on affiche ND
				fprintf(pFile,"║      %03d       %6.2f         %2d                                  ND         ║\n", pr->numeroProduit, pr->PrixUnitaire, ac->quantite);
				continue;
			}

			if (pr->Quantite < ac->quantite)
			{//s'il y'a moins de produit reservé que de produits commandés
				tag="LI"; //commande incomplète
				//on recupere la quantité de produit
				Quantite_livree = pr->Quantite;
			}else
                //sinon la commande est honoree
				Quantite_livree = ac->quantite;
            //on met à jour le stock
			pr->Quantite = pr->Quantite - ac->quantite;

            //on peut maintenant mettre à jour et calculer le prix des produits commandés
			double Montant = Quantite_livree*pr->PrixUnitaire;
			//puis l'ajouter au sous total
			SOUSTOTAL+=Montant;
        //inscription des elements dans le fichier
		fprintf(pFile, Ligne_Article, pr->numeroProduit, pr->PrixUnitaire ,ac->quantite,Quantite_livree, Montant, tag.c_str());
		}
		//calcul de l'escompte
            // on verifie si le client dispose d'une escompte, si non 0
		double ESCOMPTE=SOUSTOTAL*(cl?cl->escompte:0);
		double TOTALHT=SOUSTOTAL-ESCOMPTE;
		double TPS=TOTALHT*0.05;
		double TVQ=TOTALHT*0.09975;
        //ecriture dans le fichier des prix + taxes
        fprintf(pFile, Final_Facture,SOUSTOTAL,
		ESCOMPTE, TOTALHT, TPS, TVQ,TOTALHT+TPS+TVQ);
	}

/**************SORTIE 2***************************************/
	FILE *pFile2;
    pFile2 = fopen ("SORTIE_2.txt","w");
    if(pFile2){
    cout << "Creation de la SORTIE_2.txt" << endl;}

//	trier par nom
//
// tri avec  un tableau.
	produit *tab[count];
// creation d'une liste de produits
	produit *p = produits;

	int c;
	// pour tous les produits et produits suivants
    for(c=0;c<count;c++,p=p->next)
    {
        tab[c]=p; // on stock le tout dans le tableau
    }
	//tri rapide fourni par stdlib
	qsort(tab,count,sizeof(void *),compare);

    //ecrit l'entente dans le fichier
	fprintf(pFile2, Entete_Stock);
	// pour chaque article
for (c=0;c<count; c++){		// ecrire dans le fichier les produits classés
		fprintf(pFile2, Ligne_Stock, tab[c]->numeroProduit, tab[c]->Description, tab[c]->Vendu, (tab[c]->Quantite<=0)?"***":"   ");
	}
	// ecrire la fin de page dans le fichier
    fprintf(pFile2, Final_Stock);
    fclose(pFile);
    fclose(pFile2);

}

