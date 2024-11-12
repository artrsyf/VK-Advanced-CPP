#pragma once

struct BaggagePos
{
    int weight;

    BaggagePos() : weight(0) {}
    BaggagePos(int w) : weight(w) {}
};

struct LuggagePos
{
    int weight;

    LuggagePos() : weight(0) {}
    LuggagePos(int w) : weight(w) {}
};

struct HandLuggagePermission
{
    int allowedQuantity;
    int allowedWeight;

    HandLuggagePermission(int _allowedQuantity, int _allowedWeight) : allowedQuantity(_allowedQuantity), allowedWeight(_allowedWeight) {}
};

struct BaggagePermission
{
    int allowedQuantity;
    int allowedWeight;

    BaggagePermission(int _allowedQuantity, int _allowedWeight) : allowedQuantity(_allowedQuantity), allowedWeight(_allowedWeight) {}
};

struct BaggageSegmentSpacePermission
{
    int allowedWeight;

    BaggageSegmentSpacePermission(int _allowedWeight) : allowedWeight(_allowedWeight) {}
};