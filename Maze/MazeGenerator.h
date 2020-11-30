#pragma once
#include <iostream>
#include <Windows.h>
#include <stack>
#include <array>
#include <vector>
#include <ctime>
#include <cstdio>
#include "Generator.h"
#include "Node.h"
#include "Vertex.h"
#include "Renderer.h"

const int MAX_MAZE_WIDTH = 25;
const int MAX_MAZE_HEIGHT = 20;

class MazeGenerator
{

	private:
		uint32_t mazeWidth = 8;
		uint32_t mazeHeight = 8;
		uint32_t nVisitedNodes;
		Node startNode;

		uint32_t oldMazeHeight;

		std::stack<Node> stack;

		std::vector<Node> traversalOrder;

		std::vector<float> vertice;
		std::vector<uint32_t> indices;

		bool** maze;
		bool isInitialRenderCall;
		bool start;
		int traversalIndex; //traversal index
		uint32_t size; //size of each quad


	public:
		MazeGenerator(uint32_t mazeWidth, uint32_t mazeHeight);

		~MazeGenerator();
		void generate(uint32_t shaderProgram, uint32_t mazeWidth, uint32_t mazeHeight, uint32_t oldMazeHeight);
		void render(uint32_t shaderProgram, uint32_t speed);

		void reset();




};

