#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <algorithm> // pour transform

#include "randomnumber.hpp"
#define LIFE 10

/**
 * Jeu du pendu pour terminal
 *
 * Authors : Léo Bois, Pierre Galmiche, Mickael Bestard, Valentin Ritz.
 *
 */


// -------------------- STRUCT --------------------
/* Pertinence de séparer STRUCT et CLASS : on en discutera */

struct str_toupper // mettre en majucule un mot d'un coup
{
    char operator()(char c) const
    {
            return std::toupper(static_cast<unsigned char>(c));
    }
};


// -------------------- FUNCTIONS --------------------

/* Cette implémentation nécessite d'avoir déjà créé le fichier */
std::string random_word()
{
        std::string tmp;
        std::vector<std::string> dico;
        
        std::ifstream ifile("dictionnary.md", std::ios::in);
        if(ifile)
        {
                while (!ifile.eof())
                {
                        ifile >> tmp;
                        dico.push_back(tmp);
                }
        }
        else //on n'a pas réussi à accéder au fichier
                dico = {"MOT", "TEST", "COUCOU", "ENJOY"};
        
        RandomNumber<int> rnd(0,dico.size()-1);
        
        return dico[rnd()];
}

char get_letter()
{
        char letter;
        bool correct = false;
        
        while (!correct)
        {
                std::cout << " > ";
                std::cin >> letter;
                
                if (!(isalpha(letter)))
                        std::cout << "Not a letter, try again." << std::endl;
                else
                        correct = true;
        }
        return toupper(letter);
}//Retourne la lettre entrée en majuscule

std::string get_sword()
{
        std::string word;
        
        bool correct = false;
        while (!correct)
        {
                correct = true;
                
                std::cout << "Player 1: entrez un mot secret" << std::endl;
                std::cout << " > ";
                std::cin >> word;
                
                for (int i = 0; i < word.size(); ++i)
                {
                        if (!(isalpha(word[i])))
                        { // Code à factoriser ? (cf get_letter)
                                std::cout << "Not a word, try again." << std::endl;
                                correct = false;
                                break;
                        }
                }
        }
        std::transform(word.begin(), word.end(), word.begin(), str_toupper());
        system("clear");
        return word;
}


// -------------------- CLASS --------------------

class Game
{

public:
    
    Game(int nbPlayers) {
            
            if (nbPlayers == 1) { // pas vraiment un boolean: je laisse à 1
                    sword = random_word();
            } else {
                    sword = get_sword(); // ceci n'est pas un "getter" de la classe
            }
            
            sizeW = sword.size();
            nmistakes = 0;
            is_over = false;
            
            for(int i=0; i<sizeW; i++){
                    found.push_back(false);
            }
    }
    
    
    bool over() const { return is_over; }
    
    
    void print_state() const
    {
            std::cout << "Nombre de vies restantes : " << LIFE - nmistakes <<
                      "\nlettre à trouver : ";
            for(int i=0; i<sizeW; i++)
            {
                    if(found[i])
                            std::cout << sword[i] << " ";
                    else
                            std::cout << "_ ";
            }
            std::cout << "\n\n";
    }
    
    
    void submit(const char l)
    {
            bool isIn = false;
            for(int i=0; i<sizeW; i++)
            {
                    if(l == sword[i] && !found[i])
                    {
                            isIn = true;
                            found[i] = true;
                    }
            }
            if(!isIn)
            {
                    nmistakes++;
                    if(nmistakes == 10)
                            is_over = true;
            }
            if(std::accumulate(found.begin(), found.end(), 0) == sizeW)
                    is_over = true;
    }
    
    
    void print_result() const
    {
            std::cout << "Nombre d'erreurs : " << nmistakes << std::endl;
            if(nmistakes == LIFE)
                    std::cout << "Vous avez perdu ... Try again!" << std::endl;
            else
                    std::cout << "Vous avez gagné ... BRAVO!" << std::endl;
            
    }
    
    
private:
    
    friend std::string  random_word();
    std::string	        sword;// Par exemple SECRET (S E C R E T)
    std::vector<bool>	found;// Par exemple FFTFFT (_ _ C _ _ T)
    int                 sizeW;// Stocke la taille du mot secret
    int                 nmistakes;
    bool                is_over;
};//Fin classe Game


// -------------------- MAIN --------------------

int main()
{
        int nbPlayers;
        std::cout << "Bienvenue au jeu du Pendu !" << std::endl;
        std::cout << "Combien de joueurs ? (1/2)" << std::endl;
        std::cin >> nbPlayers;
        
        Game game(nbPlayers);
        
        game.print_state();
        while(!game.over())
        {
                // Demande au joueur de saisir une lettre (et une seule)
                char a;
                a = get_letter();
                // Met à jour les attributs de game
                game.submit(a);
                game.print_state();
        }
        game.print_result();
        return 0;
}
