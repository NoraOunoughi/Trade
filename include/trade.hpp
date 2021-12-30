/*
** EPITECH PROJECT, 2021
** B-CNA-410-PAR-4-1-trade-rilong.lin
** File description:
** trade
*/

#ifndef TRADE_HPP_
#define TRADE_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

typedef struct candles_s {
    int date;
    float high;
    float low;
    float open;
    float close;
    float volume;
}candles_t;

typedef struct settings_s {
    char *string;
    char *bot_name;
    int timebank;
    int time_per_move;
    int candle_interval;
    int candle_format;
    int candles_total;
    int candles_given;
    int initial_stack;
    float transaction_fee;
}settings_t;

typedef struct currencies_s {
    float BTC;
    float USDT;
    float ETH;
}currencies_t;

typedef struct averages_s {
    float tw_USDT_ETH;
    float fty_USDT_ETH;
    float tw_USDT_BTC;
    float fty_USDT_BTC;
    float tw_BTC_ETH;
    float fty_BTC_ETH;
}averages_t;

class trade {
    public:
        trade();
        ~trade();
        void startbot();
        void get_input();
        void check_input(string);
        void command(char *);
        void update();
        void settings();
        void action();
        void update_candles();
        void update_stacks();
        void update_USTD_ETH(char *, candles_t);
        void update_USTD_BTC(char *, candles_t);
        void update_BTC_ETH(char *, candles_t);
        float twenty_average(vector<candles_t>);
        float fifty_average(vector<candles_t>);
        void getAverages();
        void buy(string);
        void sell(string, string);
        void doNothing();

    private:
        vector<char *> _input;
        settings_t _settings;
        currencies_t _stack;
        averages_t _averages;
        vector<candles_t> _USTD_ETH;
        vector<candles_t> _USTD_BTC;
        vector<candles_t> _BTC_ETH;
};
#endif /* !TRADE_HPP_ */
