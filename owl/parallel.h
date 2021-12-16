#pragma once

#ifndef OWL_PARALLEL_H
#define OWL_PARALLEL_H

#include "mpi.h"

#include <cmath>
#include <vector>

namespace owl::parallel {
    inline int rank() {
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        return world_rank;
    }

    inline int size() {
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        return world_size;
    }

    inline int get_tasks(int total_tasks, int world_rank) {
        int world_size = size();

        int base = std::floor(total_tasks / world_size);
        int lack = total_tasks - world_size * base;
        return (world_size <= total_tasks ? base : 0) + (world_rank < lack ? 1 : 0);
    }

    inline int get_tasks(int total_tasks) {
        int world_rank = rank();

        return get_tasks(total_tasks, world_rank);
    }

    inline std::vector<int> get_tasks_per_process(int total_tasks) {
        int world_size = size();

        auto tasks = std::vector<int>();
        for (int world_rank = 0; world_rank < world_size; ++world_rank) {
            tasks.push_back(get_tasks(total_tasks, world_rank));
        }
        return tasks;
    }

    inline int get_initial_task(std::vector<int>& tasks) {
        int world_rank = rank();
        int world_size = size();

        int initial_task = 0;
        for (int i = 0; i < world_rank; ++i) {
            initial_task += tasks[i];
        }
        return initial_task;
    }

    inline int get_initial_task(int total_tasks) {
        std::vector<int> tasks = get_tasks_per_process(total_tasks);
        return get_initial_task(tasks);
    }

    inline std::vector<int> get_displacement(std::vector<int>& tasks_per_process) {
        std::vector<int> displacement;
        displacement.push_back(0);
        for (int i = 0; i < tasks_per_process.size() - 1; ++i) {
            displacement.push_back(displacement[i] + tasks_per_process[i]);
        }
        return displacement;
    }
}

#endif