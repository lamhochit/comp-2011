#include "patch.h"

#include <cstring>
#include <iostream>
using namespace std;

/**
* Append a new line to the tail.
*
* @param patch: a patch pointer
* @param line: a line pointer
*/
void append_to_bottom(Patch *patch, Line *line)
{
    if (patch->head == nullptr)
    {
        patch->head = line;
        line->next = nullptr;
        patch->tail = line;
        return;
    }
    patch->tail->next = line;
    patch->tail = line;
    line->next = nullptr;
}

void clearLine(Line *&head)
{
    if (head == nullptr)
        return;
    clearLine(head->next);
    delete head;
    head = nullptr;
}
/**
* Delete the patch and the resources owned by it.
*
* @param patch, a patch pointer.
*/
void clear(Patch *&patch)
{
    clearLine(patch->head);
    patch->head = nullptr;
    patch->tail = nullptr;
    delete patch;
    patch = nullptr;
}

void reverseLine(Line *node)
{
    if (node->next == nullptr)
        return;
    reverseLine(node->next);
    node->next->next = node;
}

/**
* Reverse the linked list of lines.
*
* @param patch, a patch pointer.
*/
void reverse(Patch *patch)
{
    Line* temp;
    reverseLine(patch->head);
    patch->head->next = nullptr;
    temp = patch->head;
    patch->head = patch->tail;
    patch->tail = temp;
}
