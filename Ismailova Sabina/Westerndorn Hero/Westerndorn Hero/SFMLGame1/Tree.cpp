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

//�������� �������� ������
void Tree::SetTexture(string route)
{
	frontTexture.loadFromFile(route);
	sprite.setTexture(frontTexture);
}

//�������� ���������� ��������
void Tree::SetOpaciveTexture(string route)
{
	opaciveTexture.loadFromFile(route);
	sprite.setTexture(opaciveTexture);
}