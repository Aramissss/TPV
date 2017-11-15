#include "Game.h"
#include <fstream>


Game::Game()
{
	level = 5;
	winX = winY = 50;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Pacman", winX, winY, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	//gamemap = new GameMap(20, 20);//Valor de prueba 20x20


	if (renderer == nullptr)//Si hay errores activa el flag
	{
		error = true;
	}
	else//Crea las texturas e entidades
	{
		//Inicializa Texturas
		pacmanText = new Texture();
		redText = new Texture();
		orangeText = new Texture();
		//pinkText = new Texture();
		blueText = new Texture();
		purpleText = new Texture();
		menuText = new Texture();
		levelCText = new Texture();
		gameOverText = new Texture();
		gameWonText = new Texture();
		
		//Fin

		//Carga texturas
		pacmanText->load(renderer, "..\\images\\characters1.png", 4, 14);
		redText->load(renderer, "..\\images\\characters1.png", 4, 14);
		orangeText->load(renderer, "..\\images\\characters1.png", 4, 14);
		//pinkText->load(renderer, "..\\images\\characters1.png", 4, 14);
		blueText->load(renderer, "..\\images\\characters1.png", 4, 14);
		purpleText->load(renderer, "..\\images\\characters1.png", 4, 14);
		menuText->load(renderer, "..\\images\\pacmanMenu.png");
		levelCText->load(renderer, "..\\images\\levelCleared.png");
		gameOverText->load(renderer, "..\\images\\gameOver.png");
		gameWonText->load(renderer, "..\\images\\gameWon.png");

		//Fin
		windowRect.x = windowRect.y = 0;
		windowRect.w = winWidth;
		windowRect.h = winHeight;
		/*Inicializa Entidades
		pacman = new Pacman(this);
		//redGhost = new Ghost(this, 0, 0, 0);
		orangeGhost = new Ghost(this, 1, 1, 2);
		pinkGhost = new Ghost(this, 2, 2, 4);
		blueGhost = new Ghost(this, 3, 3, 6);
		purpleGhost = new Ghost(this, 4, 4, 8);
		//Fin*/
	}
}
Game::~Game()
{
	//Borra entidades
	delete pacmanText;
	delete redText;
	delete blueText;
	delete orangeText;
	delete purpleText;
	delete menuText;
	//Fin

	//delete gamemap;

	//Borra entidades
	delete pacman;
	delete redGhost;
	delete orangeGhost;
	delete blueGhost;
	delete purpleGhost;
	//Fin

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

}
void Game::nextLevel(){
	exitlevel = false;
	if (level == 1){
		createMap("level01");
	}
	else if (level == 2){
		createMap("level02");
	}
	else if (level == 3){
		createMap("level03");
	}
	else if (level == 4){
		createMap("level04");
	}
	else if (level == 5){
		createMap("level05");
	}
	else exit = true;
}
void Game::createMap(string fileName)//Lee de un archivo y crea la matriz del mapa
{
	ifstream archivo;
	archivo.open("..\\levels\\"+ fileName +".dat");
	uint rows, cols;
	archivo >> rows;
	archivo >> cols;	
	int dato;
	gamemap = new GameMap(this,rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			archivo >> dato;
			if (dato == 0){
				gamemap->cells[i][j] = Empty;
			}
			else if (dato == 1){
				gamemap->cells[i][j] = Wall;
				gamemap->walls++;
			}
			else if (dato == 2){
				gamemap->cells[i][j] = Food;
				gamemap->foods++;
			}
			else if (dato == 3){
				gamemap->cells[i][j] = Vitamins;
				gamemap->vitamins++;
			}
			else if (dato == 6)
			{
				gamemap->cells[i][j] = Empty;
				redGhost = new Ghost(this, j, i, 0);
			}
			else if (dato == 5)
			{
				gamemap->cells[i][j] = Empty;
				orangeGhost = new Ghost(this, j, i, 2);
			}
			else if (dato == 4)
			{
				/*gamemap->cells[j][i] = Empty;
				pinkGhost = new Ghost(this, i, j, 0);*/
			}
			else if (dato == 7)
			{
				gamemap->cells[i][j] = Empty;
				blueGhost = new Ghost(this, j, i, 6);
			}
			else if (dato == 8)
			{
				gamemap->cells[i][j] = Empty;
				purpleGhost = new Ghost(this, j, i, 8);
			}
			else if (dato == 9)
			{
				gamemap->cells[i][j] = Empty;
				pacman = new Pacman(this, j, i);
			}
		}
	
	}
	
	gamemap->mapTexts();
	archivo.close();

}
void Game::update(){
	pacman->update();
	handleCollision();//Maneja las colisiones antes de que los fantasmas se muevan para que no puedan cruzarse
	redGhost->update();
	orangeGhost->update();
	blueGhost->update();
	purpleGhost->update();
	handleCollision();
	checkEndGame();
}
void Game::render(){
	SDL_RenderClear(renderer);
	gamemap->renderMap();
	pacman->render();
	redGhost->render();
	orangeGhost->render();
	//pinkGhost->render();
	blueGhost->render();
	purpleGhost->render();
	SDL_RenderPresent(renderer);
}
bool Game::nextCell(int x, int y, int dirX, int dirY, int& nx, int& ny)//Si la siguiente posición es una pared devuelve false
{
	nx = x + dirX;//Calcula la posición siguiente
	ny = y + dirY;
	if (nx >= gamemap->getCols())//Estas condiciones hacen que el mapa tenga forma toroide
	{
		nx = 0;
	}
	else if (nx < 0)
	{
		nx = gamemap->getCols() - 1;
	}
	if (ny < 0)
	{
		ny = gamemap->getRows() - 1;
	}
	else if (ny >= gamemap->getRows())
	{
		ny = 0;
	}
	if (gamemap->cells[ny][nx] != Wall)
	{
		return true;
	}
	else return false;
}
void Game::menuEvents()//Comprueba eventos del menú
{
	while (SDL_PollEvent(&event) && !exitMenu) {
		if (event.type == SDL_QUIT)//Si cierra la ventana termina el juego directamente
		{
			exitMenu = true;
			exit = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym != NULL){
				exitMenu = true;
			}
		}
	}
}
void Game::menuRender(){
	SDL_RenderClear(renderer);
	menuText->render(renderer, windowRect);
	SDL_RenderPresent(renderer);
}
void Game::nextLevelRender(){
	SDL_RenderClear(renderer);
	levelCText->render(renderer, windowRect);
	SDL_RenderPresent(renderer);
}
void Game::gameOverRender(){
	SDL_RenderClear(renderer);
	gameOverText->render(renderer, windowRect);
	SDL_RenderPresent(renderer);
}
void Game::gameWonRender(){
	SDL_RenderClear(renderer);
	gameWonText->render(renderer, windowRect);
	SDL_RenderPresent(renderer);
}
void Game::handleEvents()//Comprueba eventos
{
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
		{
			exit = true;	
			exitlevel = true;
		}
		else if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym == SDLK_DOWN){
				pacman->changeDir('d');
			}
			else if (event.key.keysym.sym == SDLK_UP){
				pacman->changeDir('u');
			}
			else if (event.key.keysym.sym == SDLK_RIGHT){
				pacman->changeDir('r');
			}
			else if (event.key.keysym.sym == SDLK_LEFT){
				pacman->changeDir('l');
			}
		}
	}
}
MapCell Game::getCell(int x, int y)//Devuelve el valor que hay en una celda
{
	return gamemap->cells[y][x];//La representación en la celda es al contrario
}
void Game::changeCell(int x, int y, MapCell cell)//Cambia el valor de una celda, se usa en el pacman al comer una vitamina o comida y cambiarla por empty
{
	gamemap->cells[y][x] = cell;
}
void Game::substractFood()//Resta 1 al contador de comida
{
	gamemap->foods--;
}
void Game::substractVitamin()//Resta 1 al contador de vitamina
{
	gamemap->vitamins--;
}
int Game::getRows()//Pide las filas
{
	return gamemap->rows;
}
int Game::getCols()//Pide las columnas
{
	return gamemap->cols;
}
int Game::getWinW(){//Pide el ancho de la ventana
	return winWidth;
}
int Game::getWinH(){//Pide el ancho de la altura
	return winHeight;
}
void Game::run(){
	menuRender();//Pinta la página principal
	while (!exitMenu){//Este bucle controla la pulsación del menú
		menuEvents();		
	}

	while (level < 6 && !exit){//Este bucle controle que no se salga o se haya superado el nivel máximo
		nextLevel();//Selecciona el siguiente nivel (Empieza en 1)
		while (!exitlevel){//Bucle de la pantalla de juego
			handleEvents();
			update();
			render();
			SDL_Delay(150);
		}
		delete gamemap;//Borra el gamemap actual
		if (gameover){//Si se activa el flag de game over se pinta la pantalla y posteriormente se sale del bucle
			gameOverRender();
		}
		else if(!exit){
			if (level < 6){//Si todavía hay niveles restantes se activa la pantalla de siguiente nivel en lo que se carga el mapa
				nextLevelRender();
			}
			else{
				gameWonRender();//Si llegas al nivel máximo has superado el juego				
			}
		}
	}
}
bool Game::PacmanBlueColl(){//Comprueba si hay un fantasma azul en la posición que Pacman
	if (blueGhost->getPosX() == pacman->getPosX() && blueGhost->getPosY() == pacman->getPosY()){
		return true;
	}	
	else return false;
}
bool Game::PacmanRedColl(){//Comprueba si hay un fantasma rojo en la posición que Pacman
	if (redGhost->getPosX() == pacman->getPosX() && redGhost->getPosY() == pacman->getPosY()){
		return true;
	}
	else return false;
}
bool Game::PacmanPurpleColl(){//Comprueba si hay un fantasma morado en la posición que Pacman
	if (purpleGhost->getPosX() == pacman->getPosX() && purpleGhost->getPosY() == pacman->getPosY()){
		return true;
	}
	else return false;
}
bool Game::PacmanOrangeColl(){//Comprueba si hay un fantasma naranja en la posición que Pacman
	if (orangeGhost->getPosX() == pacman->getPosX() && orangeGhost->getPosY() == pacman->getPosY()){
		return true;
	}
	else return false;
}
void Game::checkEndGame(){//Comprueba que no quedan comidas ni vitaminas en el mapa
	if (gamemap->getFoods() + gamemap->getVitamins()==0){
		gameWon();
	}
}
void Game::resetPositions(){//Reinicia las posiciones de los fantasmas y el pacman
	pacman->backToIni();
	redGhost->backToIni();
	blueGhost->backToIni();
	purpleGhost->backToIni();
	orangeGhost->backToIni();
}
void Game::gameOver(){//Termina el juego cuando has perdido
	gameover = true;
	exit = true;
	exitlevel = true;
}
void Game::gameWon(){//Termina el juego cuando ganas
	exitlevel = true;
	level++;
}

void Game::handleCollision(){//Gestiona las colisiones entre Pacman y los fantasmas
	if (PacmanBlueColl()){
		if (!blueGhost->getVulnerability()){//Si el fantasma en cuestión es invulnerable, Pacman pierde una vida
			pacman->die();
			render();//Pinta justo después de morir y hace un delay para comprender mejor la escena
			SDL_Delay(500);
			resetPositions();
		}
		else{//Vuelve a su posición inicial y se vuelve invulnerable
			blueGhost->backToIni();
			blueGhost->vulnerabilityOff();
		}
	}
	else if (PacmanRedColl()){
		if (!redGhost->getVulnerability()){//Si el fantasma en cuestión es invulnerable, Pacman pierde una vida
			pacman->die();
			render();
			SDL_Delay(500);
			resetPositions();
		}
		else{//Vuelve a su posición inicial y se vuelve invulnerable
			redGhost->backToIni();
			redGhost->vulnerabilityOff();
		}
	}
	else if (PacmanPurpleColl()){
		if (!purpleGhost->getVulnerability()){//Si el fantasma en cuestión es invulnerable, Pacman pierde una vida
			pacman->die();
			render();
			SDL_Delay(500);
			resetPositions();
		}
		else{//Vuelve a su posición inicial y se vuelve invulnerable
			purpleGhost->backToIni();
			purpleGhost->vulnerabilityOff();
		}
	}
	else if (PacmanOrangeColl()){
		if (!orangeGhost->getVulnerability()){//Si el fantasma en cuestión es invulnerable, Pacman pierde una vida
			pacman->die();
			render();
			SDL_Delay(500);
			resetPositions();
		}
		else{//Vuelve a su posición inicial y se vuelve invulnerable
			orangeGhost->backToIni();
			orangeGhost->vulnerabilityOff();
		}
	}
}
