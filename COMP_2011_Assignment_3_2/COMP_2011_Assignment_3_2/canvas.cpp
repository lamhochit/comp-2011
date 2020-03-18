#include "canvas.h"

#include <iostream>

using namespace std;

/**
* Append to the bottom.
*
* @param canvas: a canvas pointer
* @param patch: a patch pointer
*/
void append_to_bottom(Canvas *canvas, Patch *patch)
{
    if (canvas->top == nullptr)
    {
        PatchNode* newPatch = new PatchNode;
        newPatch->patch = patch;
        newPatch->above = nullptr;
        newPatch->below = nullptr;
        canvas->top = newPatch;
        canvas->bottom = newPatch;
        return;
    }
    PatchNode* newPatch = new PatchNode;
    newPatch->patch = patch;
    newPatch->below = nullptr;
    newPatch->above = canvas->bottom;
    canvas->bottom->below = newPatch;
    canvas->bottom = newPatch;
}

/**
* Delete the canvas and the resources owned by it.
*
* @param canvas, a canvas pointer.
*/
void clear(Canvas *&canvas)
{
    if (canvas == nullptr)
        return;
    
    PatchNode* nextPatch;
    Line* nextLine;
    for (PatchNode* tempPatch = canvas->top; tempPatch != nullptr; tempPatch = nextPatch)
    {
        nextPatch = tempPatch->below;
        for (Line* tempLine = tempPatch->patch->head; tempLine != nullptr; tempLine = nextLine)
        {
            nextLine = tempLine->next;
            delete tempLine;
            tempLine = nullptr;
        }
        delete tempPatch;
        tempPatch = nullptr;
    }
}

char** create_matrix(int row, int col)
{
    char** x = new char* [row];
    for (int j = 0; j < row; j++)
        x[j] = new char [col];
    
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            x[i][j] = ' ';
    
    return x;
}

/**
* Render the canvas to a buffer without border. Selected patch will be hightlighted as '@'.
*
* @param canvas, a canvas pointer.
* @return buffer, a height x width 2d array, required by the provided print function.
*/
char **render(const Canvas *canvas)
{
    if (canvas == nullptr)
    {
        return nullptr;
    }
    
    const int WIDTH = canvas->width;
    const int HEIGHT = canvas->height;
    char** buffer = create_matrix(HEIGHT, WIDTH);
    
    if (canvas->top == nullptr && canvas->bottom == nullptr)
        return buffer;
    
    for (PatchNode* tempPatchNode = canvas->bottom; tempPatchNode != nullptr; tempPatchNode = tempPatchNode->above)
    {
        int row = tempPatchNode->patch->x;
        int col = tempPatchNode->patch->y;
        for (Line* tempLine = tempPatchNode->patch->head; tempLine != nullptr; tempLine = tempLine->next)
        {
            for (int index = 0; index < (tempLine->data).length(); index++)
            {
                if ((tempLine->data)[index] != ' ')
                    if (canvas->selected == tempPatchNode)
                    {
                        if (row >= 0 && col >= 0)
                            buffer [row][col] = '@';
                    }
                    else
                    {
                        if (row >= 0 && col >= 0)
                            buffer [row][col] = (tempLine->data)[index];
                    }
                if (col + 1 < WIDTH)
                    col += 1;
                else
                    break;
            }
            if (row + 1 < HEIGHT)
                row += 1;
            else
                break;
            col = tempPatchNode->patch->y;
        }
    }
    

    return buffer;
}

/**
* Bring the selected patch node above by one node, do nothing if not applicable.
*
* @param canvas, a canvas pointer.
*/
void bring_selected_above(Canvas *canvas)
{
    if (canvas->selected->above == nullptr)
    {
        return;
    }
    
    PatchNode* selectedNode = canvas->selected;
    PatchNode* tempAbove = selectedNode->above;
    PatchNode* tempSelectedBelow = selectedNode->below;
    PatchNode* tempAboveAbove = selectedNode->above->above;
    
    if (selectedNode == canvas->bottom)
    canvas->bottom = tempAbove;
    
    if (tempAboveAbove == nullptr)
    {
        selectedNode->above = nullptr;
        canvas->top = selectedNode;
    }
    else
    {
        selectedNode->above = tempAboveAbove;
        tempAboveAbove->below = selectedNode;
    }
    selectedNode->below = tempAbove;
    
    tempAbove->above = selectedNode;
    
    if (tempSelectedBelow != nullptr)
    {
        tempSelectedBelow->above = tempAbove;
        tempAbove->below = tempSelectedBelow;
    }
    else
    {
        tempAbove->below = nullptr;
    }
}

/**
* Send the selected patch node below by one node, do nothing if not applicable.
*
* @param canvas, a canvas pointer.
*/
void send_selected_below(Canvas *canvas)
{
    if (canvas->selected->below == nullptr)
        return;

    PatchNode* selectedNode = canvas->selected;
    PatchNode* tempBelow = selectedNode->below;
    PatchNode* tempSelectedAbove = selectedNode->above;
    PatchNode* tempBelowBelow = selectedNode->below->below;
    
    if (selectedNode == canvas->top)
        canvas->top = tempBelow;
    
    if (tempBelowBelow == nullptr)
    {
        selectedNode->below = nullptr;
        canvas->bottom = selectedNode;
    }
    else
    {
        selectedNode->below = tempBelowBelow;
        tempBelowBelow->above = selectedNode;
    }
    selectedNode->above = tempBelow;
    
    tempBelow->below = selectedNode;
    
    if (tempSelectedAbove != nullptr)
    {
        tempSelectedAbove->below = tempBelow;
        tempBelow->above = tempSelectedAbove;
    }
    else
    {
        tempBelow->above = nullptr;
    }
}

/**
* Select the top patch among the patches that covers (x, y). A patch conver a position means it has an non-transparant character on it. Selection of out of bound position should be allowed, despite that the position is not rendered.
*
* @param canvas, a canvas pointer.
* @param x, canvas row to select.
* @param y, canvas column to select.
*/
void select_at(Canvas *canvas, int x, int y)
{
    canvas->selected = nullptr;
    for (PatchNode* tempPatchNode = canvas->top; tempPatchNode != nullptr; tempPatchNode = tempPatchNode->below)
    {
        int row = tempPatchNode->patch->x;
        int col = tempPatchNode->patch->y;
        for (Line* tempLine = tempPatchNode->patch->head; tempLine != nullptr; tempLine = tempLine->next)
        {
            for (int index = 0; index < (tempLine->data).length(); index++)
            {
                if ((tempLine->data)[index] != ' ' && row == x && col == y)
                {
                    canvas->selected = tempPatchNode;
                    return;
                }
                col += 1;
            }
            row += 1;
            col = tempPatchNode->patch->y;
        }
    }
}

/**
* Erase all characters at (x, y) until there is no non-transparant character on (x, y). If a patch node contains no non-transparant character after the erasing, it will be deleted. Erasing of out of bound position should be allowed, despite that the position is not rendered.
*
* @param canvas, a canvas pointer.
* @param x, canvas row to erase.
* @param y, canvas column to erase.
*/
void erase_pixel_at(Canvas *canvas, int x, int y)
{
    PatchNode* nextPatch;
    for (PatchNode* tempPatchNode = canvas->top; tempPatchNode != nullptr; tempPatchNode = nextPatch)
    {
        //int count = 1;
        bool dPatch = true;
        nextPatch = tempPatchNode->below;
        int row = tempPatchNode->patch->x;
        int col = tempPatchNode->patch->y;
        const int COL = col;
        for (Line* tempLine = tempPatchNode->patch->head; tempLine != nullptr; tempLine = tempLine->next)
        {
            for (int index = 0; index < (tempLine->data).length(); index++)
            {
                if ((tempLine->data)[index] != ' ' && row == x && col == y)
                {
                    (tempLine->data).replace(index, 1, " ");
                }
                else
                if ((tempLine->data)[index] != ' ')
                {
                    //delete patch
                    dPatch = false;
                }
                col += 1;
            }
            row += 1;
            col = COL;
        }
        if (dPatch)
        {
            //PatchNode* tempAbove = tempPatchNode->above;
            //PatchNode* tempBelow = tempPatchNode->below;
            
            if (tempPatchNode->above == nullptr && tempPatchNode->below == nullptr)
            {
                canvas->top = nullptr;
                canvas->bottom = nullptr;
            }
            else
            {
                if (tempPatchNode->above == nullptr)
                {
                    
                    (tempPatchNode->below)->above = nullptr;
                    canvas->top = tempPatchNode->below;
                }
                else
                {
                    if (tempPatchNode->below == nullptr)
                    {
                        tempPatchNode->above->below = nullptr;
                        canvas->bottom = tempPatchNode->above;
                    }
                    else
                    {
                        tempPatchNode->above->below = tempPatchNode->below;
                        tempPatchNode->below->above = tempPatchNode->above;
                    }
                }
            }
            
            delete tempPatchNode;
            tempPatchNode = nullptr;
        }
        //count += 1;
    }
}
