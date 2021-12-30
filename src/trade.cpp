/*
** EPITECH PROJECT, 2021
** B-CNA-410-PAR-4-1-trade-rilong.lin
** File description:
** every functions
*/

#include <trade.hpp>

trade::trade()
{
}

trade::~trade()
{
}

void trade::startbot(void)
{
    std::string inputLine;

    while(std::getline(std::cin, inputLine)) {
        if (inputLine.size() > 0)
            check_input(inputLine);
        command(_input.front());
        this->_input.clear();
    }
}

void trade::check_input(string getinput)
{
    char *getformat = new char [getinput.length() + 1];

    strcpy(getformat, getinput.c_str());
    getformat = strtok(getformat, " ");

    for (; getformat; getformat = strtok(NULL, " "))
        _input.push_back(getformat);
}

void trade::command(char *command)
{
    if (strcmp(command, "settings") == 0)
        this->settings();
    if (strcmp(command, "update") == 0)
        this->update();
    if (strcmp(command, "action") == 0)
        this->action();
}

void trade::settings()
{
    if (strcmp("player_names", _input[1]) == 0)
        _settings.string = _input[2];
    if (strcmp("your_bot", _input[1]) == 0)
        _settings.bot_name = _input[2];
    if (strcmp("timebank", _input[1]) == 0)
        _settings.timebank = atoi(_input[2]);
    if (strcmp("time_per_move", _input[1]) == 0)
        _settings.time_per_move = atoi(_input[2]);
    if (strcmp("candle_interval", _input[1]) == 0)
        _settings.candle_interval = atoi(_input[2]);
    if (strcmp("candles_total", _input[1]) == 0)
        _settings.candles_total = atoi(_input[2]);
    if (strcmp("candles_given", _input[1]) == 0)
        _settings.candles_given = atoi(_input[2]);
    if (strcmp("initial_stack", _input[1]) == 0)
        _settings.initial_stack = atoi(_input[2]);
    if (strcmp("transaction_fee_percent", _input[1]) == 0)
        _settings.transaction_fee = atof(_input[2]);
}

void trade::update()
{
    if (strcmp(this->_input[2], "next_candles") == 0)
        this->update_candles();
    if (strcmp(this->_input[2], "stacks") == 0)
        this->update_stacks();
}

void trade::update_USTD_ETH(char *str, candles_t USTD)
{
    char *split = strtok(str, ",");
    vector<char *> candle;

    for (; split; split = strtok(NULL, ","))
        candle.push_back(split);
    USTD.date = atoi(candle[1]);
    USTD.high = atof(candle[2]);
    USTD.low = atof(candle[3]);
    USTD.open = atof(candle[4]);
    USTD.close = atof(candle[5]);
    USTD.volume = atof(candle[6]);
    this->_USTD_ETH.push_back(USTD);
}

void trade::update_BTC_ETH(char *str, candles_t BTC)
{
    char *split = strtok(str, ",");
    vector<char *> candle;

    for (; split; split = strtok(NULL, ","))
        candle.push_back(split);
    BTC.date = atoi(candle[1]);
    BTC.high = atof(candle[2]);
    BTC.low = atof(candle[3]);
    BTC.open = atof(candle[4]);
    BTC.close = atof(candle[5]);
    BTC.volume = atof(candle[6]);
    this->_BTC_ETH.push_back(BTC);
}

void trade::update_USTD_BTC(char *str, candles_t ETHD)
{
    char *split = strtok(str, ",");
    vector<char *> candle;

    for (; split; split = strtok(NULL, ","))
        candle.push_back(split);
    ETHD.date = atoi(candle[1]);
    ETHD.high = atof(candle[2]);
    ETHD.low = atof(candle[3]);
    ETHD.open = atof(candle[4]);
    ETHD.close = atof(candle[5]);
    ETHD.volume = atof(candle[6]);
    this->_USTD_BTC.push_back(ETHD);
}

void trade::update_candles()
{
    candles_t newcandle;
    vector<char *> first_split;
    vector<char *> second_split;
    char *input_str = strtok(_input[3], ";");

    for (; input_str; input_str = strtok(NULL, ";"))
        first_split.push_back(input_str);
    update_BTC_ETH(first_split[0], newcandle);
    update_USTD_ETH(first_split[1], newcandle);
    update_USTD_BTC(first_split[2], newcandle);
}

void trade::update_stacks()
{
    char *stack_split = strtok(_input[3], ",:");
    vector<char *> stack;

    for (; stack_split; stack_split = strtok(NULL, ",:"))
        stack.push_back(stack_split);

    _stack.BTC = atof(stack[1]);
    _stack.ETH = atof(stack[3]);
    _stack.USDT = atof(stack[5]);
}

float trade::fifty_average(vector<candles_t> candle)
{
    float calc = 0.0;

    for (size_t i = candle.size() - 40; i != candle.size(); i++) {
        calc += candle[i].close;
    }
    calc = calc / 40;
    return calc;
}

float trade::twenty_average(vector<candles_t> candle)
{
    float calc = 0.0;

    for (size_t i = candle.size() - 20; i != candle.size(); i++) {
        calc += candle[i].close;
    }
    calc = calc / 20;
    return calc;
}

void trade::getAverages()
{
    this->_averages.fty_BTC_ETH = fifty_average(_BTC_ETH);
    this->_averages.fty_USDT_BTC = fifty_average(_USTD_BTC);
    this->_averages.fty_USDT_ETH = fifty_average(_USTD_ETH);
    this->_averages.tw_BTC_ETH = twenty_average(_BTC_ETH);
    this->_averages.tw_USDT_BTC = twenty_average(_USTD_BTC);
    this->_averages.tw_USDT_ETH = twenty_average(_USTD_ETH);
}

void trade::action()
{
    getAverages();

    if (this->_stack.USDT > (_USTD_ETH.back().open + 0.5) && this->_averages.tw_USDT_ETH > this->_averages.fty_USDT_ETH && _settings.timebank > _settings.transaction_fee) {
        buy("buy USDT_ETH 1");
        _settings.timebank -= _settings.transaction_fee;
    }
    else if (_stack.USDT > (_USTD_BTC.back().open + 0.5) && this->_averages.tw_USDT_BTC > this->_averages.fty_USDT_BTC && _settings.timebank > _settings.transaction_fee) {
        buy("buy USDT_BTC 1");
        _settings.timebank -= _settings.transaction_fee;
    }
    else if (_stack.BTC > (_BTC_ETH.back().open + 0.5) && this->_averages.tw_BTC_ETH > this->_averages.fty_BTC_ETH && _settings.timebank > _settings.transaction_fee) {
        buy("buy BTC_ETH 1");
        _settings.timebank -= _settings.transaction_fee;
    }
    else if (_stack.ETH > 0.2 && this->_averages.tw_USDT_ETH < this->_averages.fty_USDT_ETH && _settings.timebank > _settings.transaction_fee) {
        sell("USDT_ETH ", to_string(this->_stack.ETH * 0.25));
        _settings.timebank -= _settings.transaction_fee;
    }
    else if (_stack.BTC > 0.2 && this->_averages.tw_USDT_BTC < this->_averages.fty_USDT_BTC && _settings.timebank > _settings.transaction_fee) {
        sell("USDT_BTC ", to_string(this->_stack.BTC * 0.25));
        _settings.timebank -= _settings.transaction_fee;
    }
    else if (_stack.ETH > 0.2 && this->_averages.tw_BTC_ETH < this->_averages.fty_BTC_ETH && _settings.timebank > _settings.transaction_fee) {
        sell("BTC_ETH ", to_string(this->_stack.ETH * 0.25));
        _settings.timebank -= _settings.transaction_fee;
    }
    else
        doNothing();
}

void trade::buy(string str)
{
    cout << str << endl;
}

void trade::sell(string name, string amount)
{
    cout << "sell " + name + amount << endl;
}

void trade::doNothing()
{
    cout << "no_moves" << endl;
}
