#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctype.h>

#include "randomnumber.hpp"

/**
 * Jeu du pendu pour terminal
 *
 * Authors : Léo Bois, Pierre Galmiche, Mickael Bestard, ...
 *
 */

class Game
{
	public:
		Game(bool random = true, std::string word = "DEFAULT") {// Mickael
            if (random) {
                dico = {"MOT", "TEST", "COUCOU", "ENJOY"}; // remplir depuis fichier
                sword = random_word();
            } else {
                sword = word;// Donné par player 1. Mettre en majuscules
            }
		}

		bool over() const { return is_over; }

		void print_state() const;
		void submit(const char l);

		void print_result() const;

		std::string get_secret() {
		    return sword;
		}

	private:
		std::string random_word(){
		    RandomNumber<int> rnd(0,3);
		    return dico[rnd()];
		}

		std::string	        sword;// Par exemple SECRET (S E C R E T)
		std::vector<bool>	found;// Par exemple FFTFFT (_ _ C _ _ T)

		std::vector<std::string> dico;

		int	    nmistakes;
		bool    is_over;
};

char get_letter()// Pierre
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

int main()
{
	Game game(true);
	std::cout << "sword : " << game.get_secret() << std::endl;
	/*while(!game.over())
	{
		// Affiche par exemple :
		// nombre d'erreurs : 5  mot secret : _ _ C _ _ T
		game.print_state();
		
		// Demande au joueur de saisir une lettre (et une seule)
		char a;
		a = get_letter();
		// Met à jour les attributs de game
		game.submit(a);
	}
	game.print_result();*/
	return 0;
}
