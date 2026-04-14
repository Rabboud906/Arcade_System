#include "machine.h"

Machine::Machine(const int id, std::string name, const int cost) noexcept
        : id_(id), name_(std::move(name)), cost_(cost) {}

int Machine::id() const noexcept {
    // TODO
    return id_;
}

const std::string& Machine::name() const noexcept {
    // TODO
    return name_;
}

int Machine::play_cost() const noexcept {
    // TODO
    return cost_;
}
