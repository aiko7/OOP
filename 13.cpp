#include <iostream>
#include <cstring>
using namespace std;
class Image{
protected:
    char *image;
    char user[50];
    int width, height;
public:
    Image(char *image="untitled", char *user="unknown", int width=800, int height=800) : width(width), height(height) {
        this->image = new char [strlen(image)+1];
        strcpy(this->image,image);
        strcpy(this->user,user);
    }

    ~Image(){
        delete[] image;
    }
    virtual int fileSize() {
        return width*height*3;
    }

    friend ostream &operator<<(ostream &os, Image &image) {
        os << image.image << " " << image.user << " " << image.fileSize()<<endl;
        return os;
    }

};
class TransparentImage:public Image {
protected:
    bool transparency;
public:
     TransparentImage(bool transparency) : transparency(transparency) {

     }
     TransparentImage(char *image="untitled", char *user="unknown", int width=800, int height=800, bool transparency = true) : Image(image, user, width,height) {
         this->transparency = transparency;
     }
     int fileSize() override {
         if(transparency) {
             return width*height*4;
         }
         return width*height + width*height/8;
     }
    friend ostream &operator<<(ostream &os, TransparentImage &image) {
        os << image.image << " " << image.user << " " << image.fileSize()<<endl;
        return os;
    }

};
bool operator>(Image &i1, Image &i2) {
    return i1.fileSize()>i2.fileSize();
}
class Folder {
protected:
    char folder[255];
    char owner[50];
    Image *images[100];
    int n;
public:
    Folder(char *folder="", char *owner="") {
        strcpy(this->owner,owner);
        strcpy(this->folder,folder);
        n = 0;
//        *images = nullptr;
    }
    int folderSize() {
        int s = 0;
        for (int i = 0; i < n; ++i) {
            s += images[i]->fileSize();
        }
        return s;
    }
    Image *getMaxFile() {
        int max = images[0]->fileSize();
        int ind = 0;
        for (int i = 1; i < n; ++i) {
            if(max < images[i]->fileSize()) {
                max = images[i]->fileSize();
                ind = i;
            }
        }
        return images[ind];
    }
    Folder &operator += (Image &i) {
        TransparentImage * t = dynamic_cast<TransparentImage *>(&i);
        if(t) {
            images[n++]=t;
        }
        else {
            images[n++]=&i;
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, Folder &folder) {
        os<< folder.folder <<" "<< folder.owner <<endl;
        os<<"--"<<endl;
        for (int i = 0; i < folder.n; ++i) {
            os<<*folder.images[i];
        }
        os<<"--"<<endl;
        os<<"Folder size: "<<folder.folderSize();
        return os;
    }
    Image *operator[](int ind) {
        if(ind < 0 || ind > 100)
            return NULL;
        return images[ind];
    }
};
Folder &max_folder_size(Folder *folders, int n) {
    int max = folders[0].folderSize();
    int ind = 0;
    for (int i = 1; i < n; ++i) {
        if(max < folders[i].folderSize()) {
            max = folders[i].folderSize();
            ind = i;
        }
    }
    return folders[ind];
}
int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
