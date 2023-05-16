#pragma once

#include "ControlArea.h"

#include <QString>

using namespace std;

class FileParser
{

public:
    QString prepareFile(map<int, vector<ControlArea>> &areas);
};
