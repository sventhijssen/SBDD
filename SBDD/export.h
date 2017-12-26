#pragma once

#include <string>

class SBDD;

bool exportToFileSBDD(const sbdd::SBDD &sbddG, std::string &fileName);

bool exportToFileDOT(const sbdd::SBDD &sbddG, std::string &fileName);