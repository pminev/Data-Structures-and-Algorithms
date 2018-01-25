#pragma once

#include <random>

typedef int keyType;
typedef int valueType;
const int MAX_LEVELS = 5;

static std::random_device rd;
static std::mt19937 generator(rd());
static std::uniform_int_distribution<> uniformDistribution(1, MAX_LEVELS);

class SkipList
{
public:
	SkipList();
	SkipList(const SkipList&);
	SkipList& operator=(const SkipList&);
	~SkipList();

private:
	struct node
	{
		keyType key;
		valueType value;
		unsigned int numOfLevels;
		node** levels;

		node(keyType k, valueType v) :key(k), value(v) {
			numOfLevels = uniformDistribution(generator);
			levels = new node*[numOfLevels];
			for (int i = 0; i < numOfLevels; i++){
				levels[i] = nullptr;
			}
		}

	};

	node* pFront;
	unsigned int length;
};