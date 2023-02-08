#pragma once

class Config
{
    Config()
    {}

public:
    Config& instance() const
    {
        static Config me;
        return me;
    }    

    Config(const Config&) = delete;
    Config(Config&&) = delete;
    Config& operator=(const Config&) = delete;
    Config& operator=(Config&&) = delete;

};