#include "gamemanager.h"

GameManager::GameManager()
{
    scene = new QGraphicsScene;
    this->setFixedSize(800, 800); //Size of the view
    this->setWindowTitle("Tom & Jerry Game");

    addTheGameToTheScene();

    // Initializing timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move_tom()));
    // Start takes the number of millisecond from the slot in the timer to be executed after (no need to call it again)
    timer->start(400);

    sound = new Music; // creating an object from the Music Class

    // Initilizes music button, its size, icon, iconsize, style(wihtout border), and slot.
    music = new QPushButton();
    music->setGeometry(QRect(65 + 20*30, 30, 30, 30));
    music->setIcon(QIcon("Sound.png"));
    music->setIconSize(QSize(30, 30));
    music->setStyleSheet("QPushButton{border: 0px solid;}");
    connect(music, SIGNAL (clicked()),this, SLOT (on_music_clicked())); //connecting the slot to the button clicked event.

    scene->addWidget(music);

    this->setScene(scene);//setting the scene on the view
}

void GameManager::addTheGameToTheScene()
{
    createBoard();
    addCheese();
    addPellets();
    addLives();
    addTom();
    addJerry();
}

void GameManager::createBoard()
{
    QFile file("Board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    QString temp;
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            stream >> temp;
            BoardData[i][j] = temp.toInt();
        }
    }

    QPixmap BlockImage("Block.svg");
    BlockImage = BlockImage.scaledToWidth(30);
    BlockImage = BlockImage.scaledToHeight(30);
    QPixmap WhiteImage("White.png");
    WhiteImage = WhiteImage.scaledToWidth(30);
    WhiteImage = WhiteImage.scaledToHeight(30);

    BoardItem = new QGraphicsPixmapItem*[22];
    for (int i = 0; i < 22; i++)
        BoardItem[i] = new QGraphicsPixmapItem[22];

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            if (BoardData[i][j] < 0)
                BoardItem[i][j].setPixmap(BlockImage);
            else
                BoardItem[i][j].setPixmap(WhiteImage);

            BoardItem[i][j].setPos(70 + (30 * j), 70 + (30 * i));
            scene->addItem(&BoardItem[i][j]);
        }
    }
}
void GameManager::addCheese()
{
    cheese_arr[0] = new Cheese(1, 1, 1);
    cheese_arr[1] = new Cheese(2, 1, 20);
    cheese_arr[2] = new Cheese(3, 20, 1);
    cheese_arr[3] = new Cheese(4, 20, 20);

    // Adding 4 cheese to the screen
    for (int i = 0; i < 4; i++)
        scene->addItem(*(cheese_arr + i));
}
void GameManager::addTom()
{
    tom = new Tom(BoardData);
    scene->addItem(tom);
}
void GameManager::addJerry()
{
    // Creating Jerry and adding him to the scene
    jerry = new Jerry(BoardData);
    scene->addItem(jerry);
    // Giving the focus to Jerry
    jerry->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    jerry->setFocus();
}
void GameManager::addPellets()
{
    // Adding Power Mode Switcher on the screen
    powModeStatus = new QGraphicsTextItem("POWER MODE: Normal");
    powModeStatus->setFont(QFont("times", 12, true));
    powModeStatus->setPos(100, 40);
    scene->addItem(powModeStatus);

    // Creating 2 pellets and setting their default random positions
    pellets_arr[0] = new Pellets(1, 18, 7);//Id-1, Row-18, Col-7
    pellets_arr[1] = new Pellets(2, 6, 16);

    // Adding pellets to the screen
    for (int i = 0; i < 2; i++)
        scene->addItem(*(pellets_arr + i));

    //Creating 10 power steps images but they will not be added to the scene
    power_steps = 0;
    for(int i = 0; i < 10; i++)
        steps_arr[i] = new PSteps(i+1); //ID
}
void GameManager::addLives()
{
    // Showing the number of lives available on the screen
    lives = new QGraphicsTextItem("LIVES:");
    lives->setFont(QFont("times", 12));
    lives->setPos(100, 10);
    scene->addItem(lives);


    //Creating 3 lives and adding them to the scene
    for (int i = 0; i < 3; i++) {
        lives_arr[i] = new Lives(i+1);
        scene->addItem(*(lives_arr + i));
    }

    lives_num = 3;
}

void GameManager::check_pellets()//to check whether Jerry collided with any of the pellets
{
    for (int i = 0; i < 2; i++)
    {
        int pellet_row, pellet_col;
        pellets_arr[i]->get_row_col(pellet_row, pellet_col);
        int jerry_row, jerry_col;
        jerry->get_row_col(jerry_row, jerry_col);

        if (pellet_row == jerry_row && pellet_col == jerry_col && pellets_arr[i]->onScene()) {//Jerry collided with the pellet ON THE SCENE
            scene->removeItem(pellets_arr[i]);
            power_on();
            pellets_arr[i]->set_onScene(false);
        }
    }
}

void GameManager::power_on()
{
    jerry->set_power_mode(true);

    power_steps = 10;
    powModeStatus->setHtml("POWER MODE: Powerful");
    powModeStatus->setFont(QFont("times", 12));
    for (int i = 0; i < 10; i++)
        scene->addItem(steps_arr[i]);
}
void GameManager::check_cheese()
{
    for (int i = 0; i < 4; i++)
    {
        int cheese_row, cheese_col; // getting the initial cheese position
        cheese_arr[i]->get_row_col(cheese_row, cheese_col);

        int jerry_row, jerry_col;
        jerry->get_row_col(jerry_row, jerry_col);

        if ((cheese_row == jerry_row) && (cheese_col == jerry_col) && !jerry->get_with_cheese())
        {
            // Jerry and the cheese are in the same cell
            cheese_arr[i]->set_caught(true);

            // remove the cheese and change Jerry's picture
            scene->removeItem(cheese_arr[i]);
            QPixmap image("Jerry with Cheese.png");
            image = image.scaledToHeight(30);
            jerry->setPixmap(image);
            jerry->set_with_cheese(true);
        }

        bool caught = cheese_arr[i]->get_caught();
        if (caught && jerry->home())// if Jerry arrived home while carrying the cheese
        {
            // finding the id of the cheese that is caught and moving it into the home
            if (i == 0)
                cheese_arr[i]->set_row_col(9, 9);
            if (i == 1)
                cheese_arr[i]->set_row_col(12, 9);
            if (i == 2)
                cheese_arr[i]->set_row_col(9, 12);
            if (i == 3)
                cheese_arr[i]->set_row_col(12, 12);

            cheese_arr[i]->set_home(true);

            // Changing Jerry's picture and showing the cheese at home
            QPixmap image("Jerry.png");
            image = image.scaledToWidth(30);
            image = image.scaledToHeight(30);
            jerry->setPixmap(image);
            scene->addItem(cheese_arr[i]);
            jerry->set_with_cheese(false);
        }
    }
}
void GameManager::check_winning()
{
    int cheese_count = 0;
    for (int i = 0; i < 4; i++)
    {
        // Counting the number of cheese that are at home
        if (cheese_arr[i]->get_home())
            cheese_count++;
    }
    if (cheese_count == 4)
    {
        sound->Music_Win();

        QMessageBox msgBox;
        msgBox.setText("\tYou won!! \t\n");
        msgBox.exec();

        reset_the_game();
    }
}

void GameManager::caught_by_tom() {
    int tom_row, tom_col;
    tom->get_row_col(tom_row, tom_col);
    int jerry_row, jerry_col;
    jerry->get_row_col(jerry_row, jerry_col);

    if (tom_row == jerry_row && tom_col == jerry_col) {
        if (jerry->get_power_mode())
            tom->set_row_col(20, 10);  // Resetting Tom's position
        else
        {
            if (jerry->get_with_cheese()) {
                // Find the cheese that is with jerry to reset it

                int cheese_row, cheese_col;
                for (int i = 0; i < 4; i++)
                {
                    // Check for the caught cheese but not in home (cheese with Jerry)
                    if (cheese_arr[i]->get_caught() && !cheese_arr[i]->get_home())
                    {
                        if (i == 0)
                            cheese_row = 1, cheese_col = 1;
                        if (i == 1)
                            cheese_row = 1, cheese_col = 20;
                        if (i == 2)
                            cheese_row = 20, cheese_col = 1;
                        if (i == 3)
                            cheese_row = 20, cheese_col = 20;

                        // Reseting the pos of the cheese
                        cheese_arr[i]->set_row_col(cheese_row, cheese_col);
                        cheese_arr[i]->set_caught(false);
                        scene->addItem(cheese_arr[i]);
                        jerry->set_with_cheese(false);
                    }
                }
            }

            // Change Jerry image
            QPixmap image("Tom with Jerry.png");
            image = image.scaledToWidth(30);
            image = image.scaledToHeight(30);
            jerry->setPixmap(image);

            // Decreasing Lives
            lives_num--;
            scene->removeItem(lives_arr[lives_num]);
            sound->Music_Lose();

            if (lives_num > 0)
            {
                QMessageBox msgBox;
                msgBox.setText("\tOops! Tom caught you! \t\n\tYou now have " + QString::number(lives_num)+ " lives left.\t ");
                msgBox.exec();
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("You Lost!!");
                msgBox.exec();

                // Start the game from the beginning
                reset_the_game();
            }

            sound->Music_Game();
            // Resetting the image and position of Jerry
            QPixmap image2("Jerry.png");
            image2 = image2.scaledToWidth(30);
            image2 = image2.scaledToHeight(30);
            jerry->setPixmap(image2);

            // Resetting Tom and Jerry positions
            jerry->set_row_col(11, 11);
            tom->set_row_col(20, 10);
        }
    }
}

void GameManager::keyPressEvent(QKeyEvent *event)
{
    int row, column;
    jerry->get_row_col(row, column);

    bool moved = false;
    if (event->key() == Qt::Key_Up && BoardData[row - 1][column] >= 0)
    {
        row--;
        moved = true;
    }
    else if (event->key() == Qt::Key_Down && BoardData[row + 1][column] >= 0)
    {
        row++;
        moved = true;
    }
    else if (event->key() == Qt::Key_Right && BoardData[row][column + 1] >= 0)
    {
        column++;
        moved = true;
    }
    else if (event->key() == Qt::Key_Left && BoardData[row][column - 1] >= 0)
    {
        column--;
        moved = true;
    }

    if (moved) {
        jerry->set_row_col(row, column);
        power_steps--;
        if(power_steps>=0){
            scene->removeItem(steps_arr[power_steps]);
        }

        check_cheese(); //checking collisions with cheese
        check_pellets();
        //caught_by_tom();

        // switching off the power mode when all the steps are used
//        if (!powerModeTimer->isActive())
//        {
//            power_mode = false;
//            powMode->setHtml("Power Mode: Normal");
//        }

        if (power_steps < 1) {
            jerry->set_power_mode(false);
            powModeStatus->setHtml("POWER MODE: Normal");
            powModeStatus->setFont(QFont("times", 12));
        }
    }

    check_winning();

}
void GameManager::move_tom()
{
    // Getting Jerry's position
    int row, col;
    jerry->get_row_col(row, col);

    tom->move(row, col);
    caught_by_tom();
}

void GameManager::reset_the_game()
{
    // Resetting the Cheese
    int cheese_row, cheese_col;
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
            cheese_row = 1, cheese_col = 1;
        if (i == 1)
            cheese_row = 1, cheese_col = 20;
        if (i == 2)
            cheese_row = 20, cheese_col = 1;
        if (i == 3)
            cheese_row = 20, cheese_col = 20;

        cheese_arr[i]->set_row_col(cheese_row, cheese_col);
        cheese_arr[i]->set_caught(false);
        cheese_arr[i]->set_home(false);
    }

    // Resetting Tom and Jerry's Positions
    jerry->set_row_col(11, 11);
    tom->set_row_col(20, 10);

    // Resetting the Pellets
    scene->addItem(pellets_arr[0]);
    scene->addItem(pellets_arr[1]);

    pellets_arr[0]->set_onScene(true);
    pellets_arr[1]->set_onScene(true);

    // Resetting the lives
    for (int i = 0; i < 3; i++)
        scene->addItem(lives_arr[i]);

    // Resetting sound
    sound->Music_Game();
    lives_num=3;
}


void GameManager::on_music_clicked()
{
    sound->Toggle_Music();
}

GameManager::~GameManager()
{
    for(int i=0; i<22 ; i++)
        delete [] BoardItem[i];
    delete [] BoardItem;


    for (int i = 0; i < 4; i++)
        delete cheese_arr[i];

    for (int i = 0; i < 2; i++)
        delete pellets_arr[i];

    for (int i = 0; i < 10; i++)
        delete steps_arr[i];

    for (int i = 0; i < 3; i++)
        delete lives_arr[i];

    delete lives;

    delete tom;
    delete jerry;
    delete sound;
    delete music;

    delete scene;
}
