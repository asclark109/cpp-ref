#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>

std::string getUserAnimal() {
	std::string animal;
	std::cout << "enter animal: ";
	std::getline(std::cin, animal);
	return animal;
}

struct SolutionAnswers {
	std::vector<bool> answerSet; // idx == idx of question; bool == y/n response

	void addResponse(bool satisfies) {
		answerSet.push_back(satisfies);
	}
};

struct Question {
	Question(std::string _qStr) : qStr(_qStr) {};
	std::string qStr; // question string
	std::map<std::string, bool> answerSet; // animal as key, y/n as value (bool)

	// returns vector of strings of animals have answers of "true"
	// to the question or "false", depending on querySatisfies parameter.
	// if querySatisfies==true, the animals returned are those that answer
	// "yes" to the question
	std::vector<std::string> getAnimalsSatisfying(bool querySatisfies) {
		std::vector<std::string> animals;
		std::string animal;
		bool satisfies;
		for (auto itr = answerSet.begin(); itr != answerSet.end(); ++itr) {
			animal = itr->first;
			satisfies = itr->second;
			if ((satisfies && querySatisfies) || (!satisfies && !querySatisfies)){
				animals.push_back(animal);
			}
		}
		return animals;
	}

	// accepts a vector of candidate Animal solutions and creates a new vector
	// of candidate Animal solutions that excludes the animals not satisfying
	// the response to this question
	std::set<std::string> trimOutInvalidAnimals(std::set<std::string> candidateAnimalSolns, bool querySatisfies) {
		std::set<std::string> satisfyingAnimals;
		std::string animal;
		bool satisfies;
		for (auto itr = answerSet.begin(); itr != answerSet.end(); ++itr) {
			animal = itr->first;
			satisfies = itr->second;
			// if the animal is a candidate Animal to the soln, consider removing it if response to this question
			// eliminates this animal as possible solution
			if (candidateAnimalSolns.find(animal) != candidateAnimalSolns.end()) {
				if ((satisfies && querySatisfies) || (!satisfies && !querySatisfies)) {
					satisfyingAnimals.insert(animal);
				}
			}
		}
		return satisfyingAnimals;
	}

	void addAnswer(std::string animal, bool satisfies) {
		answerSet[animal] = satisfies; // overwrites older solution if the animal was in answerSet already
	}
};

class AiEngine {
private:
	std::vector<Question> questions;
	std::set<std::string> allAnimals; // consider refactoring to not maintain parallel data structures
	std::set<std::string> candidateAnimals;
	SolutionAnswers solnAnswers;
	int qIdx = 0;

	Question currentQuestion() { return questions[qIdx]; };
public:
	AiEngine(std::set<std::string> initAnimals, std::vector<Question> initQuestions) {
		allAnimals = initAnimals;
		candidateAnimals = allAnimals;
		questions = initQuestions; 
	}

	// prepares AiEngine for new game. call this AFTER internalizeSoln.
	void reset() {
		candidateAnimals = allAnimals; // want copy
		SolutionAnswers solnAnswers; // want new (blank)
		qIdx = 0;
	};

	// this is an end-game action where the AI internalizes the final solution:
	// it memorizes the user's responses to questions ask prior and associates them with the revealed Animal,
	// and it adds the satisfying Question for the revealed animal to its set of questions it can ask the
	// user in a future game
	void internalizeSoln(std::string correctAnimal, std::string satisfyingQuestion) {
		// we now know the correct Animal, a satisfying question, and this animals
		// answers to previous questions asked. we need to:
		// (1) update our vector of questions to add solutions for the new animal
		// (2) add a new question to our set of questions we can ask the user

		// (1)
		for (size_t i = 0; i < questions.size(); i++)
		{
			questions[i].addAnswer(correctAnimal, solnAnswers.answerSet[i]);
		}

		// (2)
		Question newQ(satisfyingQuestion);
		newQ.addAnswer(correctAnimal, true);
		questions.push_back(newQ);
		allAnimals.insert(correctAnimal);
	};

	// returns the AiEngine's current best guess to the solution based on user responses in the game
	// so far. assumes the AiEngine is aware of at least one animal (i.e., allAnimals.size() > 0)
	std::string guess() { 
		// if the set of candidate solns is larger than size 1, then there are multiple answer
		// possibilities equally as good. arbitrary choose the first candidate soln in the set;
		// if the candidate solution set is empty, arbitrarily guess the first animal stored 
		// memory among all animals registered.
		std::string bestAnswer;
		if (candidateAnimals.size() > 0) {
			auto itr = candidateAnimals.begin();
			bestAnswer = *itr;
		} else {
			auto itr = allAnimals.begin();
			bestAnswer = *itr;
		}
		return bestAnswer;
	};

	// returns the number of questions in the AiEngine's memory
	int numQuestions() { return questions.size(); };

	// displays the current question, continuously asks user for y/n response.
	// upon a valid response, the AI adds the response in memory, and trims
	// candidate solutions down to a smaller set of possible solutions.
	void AskQuestion() {
		std::string response;
		bool satisfies;
		// continously ask the question until valid response received (y/n)
		while (true) {
			std::cout << currentQuestion().qStr << "(y/n): "; // display question
			std::getline(std::cin, response);
			if (response == "y") {
				satisfies = true;
				break;
			} else if (response == "n") {
				satisfies = false;
				break;
			}
			std::cout << "please enter 'y' or 'n'" << std::endl;
		}

		// (1) save response to question in solution
		solnAnswers.addResponse(satisfies);
		
		// (2) remove candidate solutions based on response
		// for the current question and response, remove from the set of possible animals in the solution set
		// all the animals that can be eliminated based on the question, response.
		candidateAnimals = currentQuestion().trimOutInvalidAnimals(candidateAnimals, satisfies);

		// advance to next question (if at last question, just stay there)
		// client code will invoke this function numQuestions() amount of times
		// on a single game iteration
		if (qIdx != numQuestions() - 1)
			qIdx++;
	};
};

int main() {

	// set up AI
	Question initQ("can you ride it?");
	initQ.addAnswer("horse", true);
	initQ.addAnswer("swan", false);
	std::vector<Question> initQuestions = { initQ };
	std::set<std::string> initAnimals = { "horse", "swan"};
	AiEngine aiEngine(initAnimals, initQuestions);

	// main game loop
	while (true) {

		// (1) choose secret animal
		std::string secretAnimal = getUserAnimal();

		// (2) AI continuously asks the user questions and internalizes the responses
		for (size_t i = 0; i < aiEngine.numQuestions(); i++)
		{
			aiEngine.AskQuestion();
		}
		// (3) AI makes a final guess after it has exhausted its question
		std::string bestGuess = aiEngine.guess();

		// (4) evaluate end-game result
		// if AI is correct, just proceed with another game.
		// if AI is wrong, the AI internalizes the game to become 'smarter' and asks the user for an identifying question
		std::cout << "AI: Is it a '" << bestGuess << "'? ";
		if (bestGuess == secretAnimal) {
			std::cout << "CORRECT! '" << bestGuess << "'" << " was the correct answer!" << std::endl;
		}
		else {
			std::cout << "WRONG! '" << secretAnimal << "'" << " was actually the correct answer!" << std::endl;
			std::cout << "what question distinguishes a '" << secretAnimal << "' from a " << "'" << bestGuess << "'?:" << std::endl;
			std::string satisfyingQuestion;
			std::getline(std::cin, satisfyingQuestion);
			aiEngine.internalizeSoln(secretAnimal, satisfyingQuestion);
		}

		// (5) reset for new game
		aiEngine.reset();
	}




	return 0;
}