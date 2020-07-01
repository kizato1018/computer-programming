#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "game.h"

int Input() {
    std::string option;
    getline( std::cin, option );
    return atoi( option.c_str() );
}

// WorldPlayer
Player& WorldPlayer::Get_Player( const int idx ) {
    return *players_[idx];
}

bool WorldPlayer::Add_Player( Player *newPlayer ){
    players_.push_back( newPlayer );
    return true;
}

// WorldMap
bool WorldMap::Get_Map( std::ifstream &fin ){
    const int max_length = 200;
    int id = 0;

    while( !fin.eof() ) {
        std::string line;
        getline(fin, line);
        if(line.size() < 2) continue;
        if(line[0] == 'U') {
            std::stringstream ss;
            char type = 0;
            std::string name;
            int price = 0;
            int upgrade_price = 0;
            int travel_fine[5] = {0};
            ss << line;
            ss >> type >> name >> price >> upgrade_price;
            for(int i = 0; i < 5; ++i)
                ss >> travel_fine[i];
            MapUnit* new_unit = new UpgradableUnit( id, name, price, upgrade_price, travel_fine );
            units_.push_back( new_unit );
        }
        else if(line[0] == 'C') {
            std::stringstream ss;
            char type = 0;
            std::string name;
            int price = 0;
            int fine = 0;

            ss << line;
            ss >> type >> name >> price >> fine;
            MapUnit* new_unit = new CollectableUnit( id, name, price, fine );
            units_.push_back( new_unit );
        }
        else if(line[0] == 'R') {
            std::stringstream ss;
            char type = 0;
            std::string name;
            int price = 0;
            int fine = 0;

            ss << line;
            ss >> type >> name >> price >> fine;
            MapUnit* new_unit = new RandomCostUnit( id, name, price, fine );
            units_.push_back( new_unit );
        }
        else if(line[0] == 'J') {
            std::stringstream ss;
            char type = 0;
            std::string name;
            ss << line;
            ss >> type >> name;
            MapUnit* new_unit = new JailUnit( id, name );
            units_.push_back( new_unit );
        }
        else {
            continue;
        }

        id+=1;
    }

    number_map_unit_ = id;

    return true;
}

MapUnit& WorldMap::Get_Unit( const int id )
{
    return *(units_[id]);
}

// Game
void Game::Init( std::ifstream &fin )
{
    srand( time( 0 ) );
    game_over_ = false;

    world_map_.Get_Map( fin );

    int number_player = 0;
    std::cout << "How many players?(Maximum:4)...>";
    number_player = Input();
    if(number_player > 4) {
        number_player = 4;
    }
    else if(number_player < 1) {
        number_player = 1;
    }
    world_player_.Set_Number_Player( number_player );
    world_player_.Set_Total_Number( number_player );

    std::string name;
    std::string default_name[4];
    default_name[0] = "aaa";
    default_name[1] = "bbb";
    default_name[2] = "ccc";
    default_name[3] = "ddd";
    for( size_t i = 0; i < number_player; ++i) {
        std::cout << "Please input player " << i+1 << "'s name (Default: " << default_name[i] << ")...>";
        getline( std::cin, name );
        if( name.empty() ) {
            name = default_name[i];
        }
        if( !New_Player( i, name ) ) {
            i-=1;
        }
    }



    return;
}

bool Game::New_Player( const int id, const std::string name )
{
    Player *newPlayer = new Player(id, name);

    if( world_player_.Add_Player( newPlayer ) )
        return true;
    return false;
}

Condition Game::Move( const int id )
{
    Player &cur_player = world_player_.Get_Player(id);
    if(cur_player.Is_Bankrupt())
        return BANKRUPT;
    if( !(cur_player.Is_Movable()) )
        return JAIL;

    std::cout << cur_player.Get_Player_Name() << ", your action? (1:Dice [default] / 2:Exit)...>";
    int option = Input();

    if( option == 2 )
    {
        Game_Over();
        return NOTHING;
    }

    int dice = cur_player.Roll_Dice();
    int location = cur_player.Get_Location();
    std::cout << "location: " << location << std::endl;
    world_map_.Get_Unit(location).Leave(cur_player.Get_Id());
    int number_unit = world_map_.Get_Number_Unit();
    int move_target = ( location + dice );
    if(move_target >= number_unit) {
        move_target %= number_unit;
        cur_player.Do_Act(GAIN, world_map_.Round_Reward());
        std::cout << cur_player.Get_Player_Name() << ", you got $" << world_map_.Round_Reward() << std::endl;
    }
    std::cout << "move target: " << move_target << std::endl;
    cur_player.Set_Location( move_target );
    MapUnit &cur_unit = world_map_.Get_Unit( move_target );
    Condition event = cur_unit.Travel( id );

    return event;
}

void Game::Show_A_Unit( const int id )
{
    int total_player = world_player_.Get_Total_Number();
    int number_player = world_player_.Get_Number_Player();
    int collection_cnt = 0;
    for( size_t o = 0; o < number_player; o++ )
        if( world_map_.Get_Unit( id ).Get_Host() == world_player_.Get_Player( o ).Get_Id() )
            collection_cnt = world_player_.Get_Player( o ).Get_Collection_Cnt();
    world_map_.Get_Unit( id ).Map_Show( total_player, collection_cnt );
}

void Game::Show_Map() {
    int number_unit = world_map_.Get_Number_Unit();
    for( size_t i = 0; i < number_unit / 2; ++i )
    {
        Show_A_Unit( i );
        std::cout << "       ";
        Show_A_Unit( number_unit - i - 1 );
        std::cout << std::endl;
    }
    if( number_unit % 2 )
    {
        Show_A_Unit( number_unit / 2 );
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Game::Show_Info( const int id )
{
    int number_unit = world_map_.Get_Number_Unit();
    int number_player = world_player_.Get_Total_Number();
    Show_Map();
    for( size_t i = 0; i < number_player; ++i )
    {
        if( world_player_.Get_Player( i ).Is_Bankrupt() )
            continue;
        if( id == i )
            std::cout << "=>";
        else
            std::cout << "  ";

        world_player_.Get_Player( i ).Player_Show();
        std::cout << std::endl;;
    }
    std::cout << std::endl;
    return;
}


void Game::Travel( const int id, Condition event )
{
    Player &cur_player = world_player_.Get_Player(id);
    MapUnit &cur_unit = world_map_.Get_Unit( cur_player.Get_Location() );
// --------------------------------------------------
    Show_Event( event, cur_player, cur_unit );
    Execute_Event( event, cur_player, cur_unit );
    return;
}



void Game::Show_Event( const Condition event, const Player &cur_player, const MapUnit &cur_unit )
{
    if( event == BUYABLE_U || event ==  BUYABLE_R || event ==  BUYABLE_C )
    {
        std::cout << cur_player.Get_Player_Name() << ", do you want to buy " << cur_unit.Get_Unit_Name() << "? (1: Yes [default] / 2: No) ...>";
    }

    else if( event == UPGRADABLE )
    {
        std::cout << cur_player.Get_Player_Name() << ", do you want to upgrade " << cur_unit.Get_Unit_Name() << "? (1: Yes [default] / 2: No) ...>";
    }

    return;
}

void Game::Execute_Event( const Condition event, Player &cur_player, MapUnit &cur_unit )
{

    if( event == BUYABLE_U ) {
        int option = Input();
        if( option != 2 ) {
            UpgradableUnit *upgradalbe_unit = dynamic_cast<UpgradableUnit *>(&cur_unit);
            if( cur_player.Do_Act( BUY, upgradalbe_unit->Buy_price() ) )
                upgradalbe_unit->Host( cur_player.Get_Id() );
            std::cout << "You pay $" << upgradalbe_unit->Buy_price() << " to buy " << upgradalbe_unit->Get_Unit_Name() << std::endl;
            std::cout << "Press any key to continue." << std::endl;
            getchar();
        }
    }

    else if( event == BUYABLE_C ){
        int option = Input();
        if( option != 2 ) {
            CollectableUnit *collectable_unit = dynamic_cast<CollectableUnit *>(&cur_unit);
            if( cur_player.Do_Act( BUY_C, collectable_unit->Buy_price() ) )
                collectable_unit->Host( cur_player.Get_Id() );
            std::cout << "You pay $" << collectable_unit->Buy_price() << " to buy " << collectable_unit->Get_Unit_Name() << std::endl;
            std::cout << "Press any key to continue." << std::endl;
            getchar();
        }
    }

    else if( event == BUYABLE_R ){
        int option = Input();
        if( option != 2 ) {
            RandomCostUnit *random_unit = dynamic_cast<RandomCostUnit *> (&cur_unit);
            if( cur_player.Do_Act( BUY, random_unit->Buy_price() ) )
                random_unit->Host( cur_player.Get_Id() );
            std::cout << "You pay $" << random_unit->Buy_price() << " to buy " << random_unit->Get_Unit_Name() << std::endl;
            std::cout << "Press any key to continue." << std::endl;
            getchar();
        }
    }

    else if( event == PAYMENT_U )
    {
        Player &creditor = world_player_.Get_Player( cur_unit.Get_Host() );
        if( cur_player.Do_Act( PAY, cur_unit.Get_Fine() ) )
        {
            creditor.Do_Act( GAIN, cur_unit.Get_Fine() );
            std::cout << cur_player.Get_Player_Name() << ", you must pay $" << cur_unit.Get_Fine() << " to Player " <<  creditor.Get_Id() << " (" << creditor.Get_Player_Name() << ")" << std::endl;
        }
        else
        {
            creditor.Do_Act( GAIN, cur_player.Get_Money() );
            Bankrupt_( cur_player );
            std::cout << cur_player.Get_Player_Name() << ", you bankrupt!!" << std::endl;
        }

        std::cout << "Press any key to continue." << std::endl;
        getchar();
    }

    else if( event == PAYMENT_C )
    {
        Player &creditor = world_player_.Get_Player( cur_unit.Get_Host() );
        int fine = 0;
        fine = cur_unit.Get_Fine() * creditor.Get_Collection_Cnt();
        if( cur_player.Do_Act( PAY, fine) )
        {
            creditor.Do_Act( GAIN, fine );
            std::cout << cur_player.Get_Player_Name() << ", you must pay $" << fine << " to Player " <<  creditor.Get_Id() << " (" << creditor.Get_Player_Name() << ")" << std::endl;
        }
        else
        {
            creditor.Do_Act( GAIN, cur_player.Get_Money() );
            Bankrupt_( cur_player );
            std::cout << cur_player.Get_Player_Name() << ", you bankrupt!!" << std::endl;
        }

        std::cout << "Press any key to continue." << std::endl;
        getchar();
    }

    else if( event == PAYMENT_R )
    {
        Player &creditor = world_player_.Get_Player( cur_unit.Get_Host() );
        int fine = 0;
        fine = cur_unit.Get_Fine() * cur_player.Roll_Dice();
        if( cur_player.Do_Act( PAY, fine ) )
        {
            creditor.Do_Act( GAIN, fine );
            std::cout << cur_player.Get_Player_Name() << ", you must pay $" << fine << " to Player " <<  creditor.Get_Id() << " (" << creditor.Get_Player_Name() << ")" << std::endl;
        }
        else
        {
            creditor.Do_Act( GAIN, cur_player.Get_Money() );
            Bankrupt_( cur_player );
            std::cout << cur_player.Get_Player_Name() << ", you bankrupt!!" << std::endl;
        }

        std::cout << "Press any key to continue." << std::endl;
        getchar();
    }

    else if( event == UPGRADABLE )
    {
        int option = Input();
        if( option != 2 )
        {
            UpgradableUnit *upgradable_unit = dynamic_cast<UpgradableUnit *> (&cur_unit);
            if( upgradable_unit->Get_Level() == 5) {
                std::cout << "This is the maximum level" << std::endl;
            }
            else if( cur_player.Do_Act( UPGRADE, upgradable_unit->Upgrade_price() ) ) {
                upgradable_unit->Upgrade();
                std::cout << "You pay $" << upgradable_unit->Upgrade_price() << " to upgrade USA to Lv." << upgradable_unit->Get_Level() << std::endl;
            }
            std::cout << "Press any key to continue." << std::endl;
            getchar();
        }
    }

    else if( event == JAIL )
    {
        cur_player.Do_Act( TOJAIL );
        std::cout << "You are in jail " << cur_unit.Get_Unit_Name() << std::endl;
        std::cout << "Press any key to continue." << std::endl;
        getchar();
    }
    return;
}


void Game::Bankrupt_( Player &bankrupt )
{
    int id = bankrupt.Get_Id();
    int number_unit = world_map_.Get_Number_Unit();

    for( int i = 0; i < number_unit; ++i )
    {
        MapUnit &cur_unit = world_map_.Get_Unit( i );
        if( id == cur_unit.Get_Host() )
            cur_unit.Release();
    }

    bankrupt.Bankrupt();

    int number_player = world_player_.Get_Number_Player();
    world_player_.Set_Number_Player( number_player - 1 );
    return;
}
