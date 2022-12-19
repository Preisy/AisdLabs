cmake_minimum_required(VERSION 3.16.3)
project(lab_2)

set(CMAKE_CXX_STANDARD 14)


include_directories(Src)
include_directories(Lib)

add_executable(lab_2 main.cpp
        Src/View/Output.cpp
        Src/Models/Entities/ProcessModel.cpp
        Src/Controllers/ProcessScheduler/ProcessSchedulerController.cpp
        Src/Models/Services/ProcessScheduler/ProcessSchedulerService.cpp
        Src/Controllers/ProcessScheduler/Realization/RoundRobinController.cpp
        Src/Models/Services/ProcessScheduler/Realization/RoundRobinService.cpp)

