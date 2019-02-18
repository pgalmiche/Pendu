#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <ctype.h>

/**
 * Jeu du pendu pour terminal
 *
 * Authors : Léo Bois, Pierre Galmiche, ...
 *
 */

class Game
{
	public:
		Game();

		bool over() const { return is_over; }

		void print_state() const;
		void submit(const char l);

		void print_result() const;

	private:
		std::string		random_word();

		std::vector<char>	sword;// Par exemple SECRET (S E C R E T)
		std::vector<bool>	found;// Par exemple FFTFFT (_ _ C _ _ T)

		int			nmistakes;
		bool			is_over;
};

char get_letter()//Pierre
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
	Game game();
	while(!game.over())
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
	game.print_result();
	return 0;
}
