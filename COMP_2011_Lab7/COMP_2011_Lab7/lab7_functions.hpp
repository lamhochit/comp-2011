# include "lab7.h"

// Utility functions
void _print(const ASCIIImage& img, bool verbose)
{
    if(verbose)
    {
        cout<<"row: "<<img.row<<endl;
        cout<<"col: "<<img.col<<endl;
        cout<<"valid?: "<<(_check_image_size(img)? "True":"False")<<endl;
        cout<<"data: "<<endl;
    }
    for(int i=0; i<img.row; i++)
    {
        for(int j=0; j<img.col; j++)
            cout<<img.data[i][j];
        cout<<endl;
    }
}

bool _check_image_size(const ASCIIImage& img)
{
    int row, col;
    for(int i=0; i<MAX_IMAGE_SIZE; i++)
    {
        row = i;
        if(img.data[row][0] == 0)
            break;
    }
    for(int i=0; i<MAX_IMAGE_SIZE; i++)
    {
        col = i;
        if(img.data[0][col] == 0)
            break;
    }
    if(row != img.row || col != img.col)
        return false;
    return true;
}

// Function for ploting the ASCIIImage
void plot(const ASCIIImage& img)
{
    cout<<endl;
    _print(img);
    cout<<endl;
}

// FUNCTION 1
/**
 * TODO:
 * Read the file defined by 'path', and initialize the 'img' with the contents of the file.
 * It should return true if it reads & initializes successfully. Otherwise, it should return False.
 * Note:
 * The row number of the ASCII image locates at the 1st line of the file.
 * The column number of the ASCII image locates at the 2nd line of the file.
 * The following contents are the data of the ASCII image.
 * You can assume the data is square and contains no space.
 **/
bool read_image(ASCIIImage& img, const char path[])
{
    ifstream ifs(path);
    if (!ifs)
    {
        cerr << "Error: Can't open \"" << path << "\"\n";
        
        return false;
    }
    else
    {
        ifs >> img.row >> img.col;
        for (int i = 0; i < img.row; i++)
            for (int j = 0; j < img.col; j++)
                ifs >> img.data[i][j];
        return true;
    }
}

// FUNCTION 2
/**
 * TODO:
 * Write 'img' into the file defined by 'path' if 'img' is valid.
 * It should return true if it writes successfully. Otherwise, it should return False.
 * The data format should coincide with the notification of FUNCTION 1.
 * Note:
 * You can validate the 'img' with '_check_image_size'.
 * Of course, you can implement your own validation function.
 **/
bool write_image(const ASCIIImage& img, const char path[])
{
    ifstream ifs(path);
    if (!ifs)
    {
        cerr << "Error: Can't open \"" << path << "\"\n";
        return false;
    }
    else
    {
        ofstream ofs(path);
        if (!ofs)
        {
            cerr << "Error: Can't open \"" << path << "\"\n";
        }
        char c; ifs.get(c);
        while (!ifs.eof())
        {
            ofs.put(c);
            ifs.get(c);
        }
        ifs.close();
        ofs.close();
        return true;
    }
    
}

// FUNCTION 3
/**
 * TODO:
 * Rotate the 'img' right by 90 degrees.
 * Note:
 * You have to make sure the result is also a valid ASCIIImage.
 **/
void rotate_clockwise(ASCIIImage& img)
{
    for (int i = 0; i < img.row; i++)
        for (int j = 0; j < img.col; j++)
            cout << "" << endl;
}

// FUNCTION 4
/**
 * TODO:
 * Flip the 'img' horizontally.
 * Note:
 * You have to make sure the result is also a valid ASCIIImage.
 **/
void flip_horizontally(ASCIIImage& img)
{
    img = img;
}
