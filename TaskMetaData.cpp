#include "TaskMetaData.h"

TaskMetaData::TaskMetaData(std::string location, std::string time):
    d_location(location),
    event_time(time)
    {}

TaskMetaData::TaskMetaData(std::string subject):
    d_subject(subject)
    {}

TaskMetaData::TaskMetaData(std::vector<std::string> list):
    shopping_list(list)
    {};