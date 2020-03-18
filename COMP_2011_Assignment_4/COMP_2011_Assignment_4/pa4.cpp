/*
* COMP2011 (Fall 2019) Assignment 4: The Web System
* File: pa4.cpp
*
* Student name: LAM Ho Chit
* Student ID: 20607878
* Student email: hclamao@connect.ust.hk
*
* Note: This is for your implementation.
* Please first fill your information above.
* Feel free to add your helper functions in pa4.cpp.
* There is no need to change other files.
*/

#include "web.h"

WebNode::WebNode(const char* webAddress, const char* anchorText, int height)
{
    //Set basic address and anchor text informatio
    
    m_webAddress = new char [strlen(webAddress)+1];
    strcpy(m_webAddress, webAddress);
    m_anchorText = new char [strlen(anchorText)+1];
    strcpy(m_anchorText, anchorText);
    
    //base case, terminate recursion if level is maxed
    if (!isHTMLfile(webAddress) || height <= 1)
    {
        //set the number of hyperlinks to 0 if there is no next layer
        m_numOfHyperlinks = 0;
        m_hyperlink = nullptr;
    }
    else
    {
        char** anchorTags = nullptr;
        extractAllAnchorTags(webAddress, anchorTags, m_numOfHyperlinks);
    //locate all hyperlinks
        m_hyperlink = new WebNode* [m_numOfHyperlinks];
        for (int i = 0; i < m_numOfHyperlinks; i++)
        {
            const char* webAdd = getWebAddress(anchorTags[i]);
            const char* anchorTxt = getAnchorText(anchorTags[i]);
            m_hyperlink[i] = new WebNode(webAdd, anchorTxt, height - 1);
            delete [] webAdd;
            delete [] anchorTxt;
            webAdd = nullptr;
            anchorTxt = nullptr;
        }
        for (int i = 0 ; i < m_numOfHyperlinks; i++)
        {
            delete[] anchorTags[i];
            anchorTags[i] = nullptr;
        }
        delete[] anchorTags;
        anchorTags = nullptr;
    }
}

WebNode::~WebNode()
{
    
    for (int i = 0; i < m_numOfHyperlinks; i++)
    {
        delete m_hyperlink[i];
        m_hyperlink[i] = nullptr;
    }
    delete [] m_hyperlink;
    m_hyperlink = nullptr;
    
    delete [] m_webAddress;
    delete [] m_anchorText;
    m_webAddress = nullptr;
    m_anchorText = nullptr;
    
    m_numOfHyperlinks = 0;
}

void WebNode::printGraph(int depth) const
{
    for (int i = 0; i < depth; i++)
    {
        cout << "\t";
    }
    cout << anchorText() << " (url: " << webAddress() << ")" << endl;
    if (hyperlink() == nullptr)
        return;
    else
    {
        for (int i = 0; i < m_numOfHyperlinks; i++)
            hyperlink()[i]->printGraph(depth + 1);
    }
}

const WebNode* WebNode::findParent(const char* webAddress) const
{
    if (hyperlink() == nullptr)
        return nullptr;
    
    for (int i = 0; i < m_numOfHyperlinks; i++)
    {
        if (strcmp(hyperlink()[i]->webAddress(), webAddress) == 0)
            return this;
        else
            if (hyperlink()[i]->findParent(webAddress) != nullptr)
                return hyperlink()[i]->findParent(webAddress);
    }
    return nullptr;
}

void WebNode::printPath(const char* address1, const char* address2) const
{
    int count = 1;
    char* temp = new char [strlen(address2)+1];
    strcpy(temp, address2);
    while (strcmp(temp, address1) != 0)
    {
        count += 1;
        if (findParent(temp) != nullptr)
            strcpy(temp, findParent(temp)->webAddress());
        else
        {
            count = 0;
            break;
        }
    }
    if (count != 0)
    {
        char** tempArray = new char* [count + 1];
        strcpy(temp,address2);
        for (int i = count - 1; i >= 0; i--)
        {
            tempArray[i] = new char[strlen(temp)+1];
            strcpy(tempArray[i], temp);
            if (i > 0)
            {
                strcpy(temp, findParent(temp)->webAddress());
            }
        }
        for (int i = 0; i < count; i++)
        {
            cout << tempArray[i] << " ";
        }
        for (int i = 0; i < count; i++)
        {
            delete [] tempArray[i];
        }
        delete [] tempArray;
    }
    else
        cout << "Path not found";
    
    delete [] temp;
    temp = nullptr;
}
