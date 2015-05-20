#include "Tree.h"

Tree::Tree()
{
	destroyable = false;
	shootable = false;
	collision = false;
	dead = false;

	frontTexture.loadFromFile("tileset/tree.png");
	sprite.setTexture(frontTexture);
	opaciveTexture.loadFromFile("tileset/opaciveTree.png");
}

Tree::~Tree()
{

}

//Добавить текстуру дерева
void Tree::SetTexture(string route)
{
	frontTexture.loadFromFile(route);
	sprite.setTexture(frontTexture);
}

//Добавить прозрачную текстуру
void Tree::SetOpaciveTexture(string route)
{
	opaciveTexture.loadFromFile(route);
	sprite.setTexture(opaciveTexture);
}