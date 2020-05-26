//
// Created by 20694 on 2020/5/12.
//
//w5,a4,a3,a2,a1,d4,d3,d2,d1,
//w5=a4=a3=a2=a1=d4=d3=d2=d1=0
#include "pawn_score.h"

int win5(const int *left, const int *right, int length, int color){
    if(5==length) {
        return w5;
    }
    else return 0;
}
int alive4(const int *left,const int *right,int length,int color){
    int color_;
    color_ = get_color_(color);
    if(length!=4||left[1]==color_||right[1]==color_) return 0;
    else return a4;
}
int dead4(const int *left,const int *right,int length,int color){
    int color_;
    color_ = get_color_(color);
    switch (length){
        case 4:{
            if(left[1]==color_&&right[1]==color_) return 0;
            else{
                return d4;
            }
        }
        case 3:{
            if((left[1]==empty&&left[2]==color)||(right[1]==empty&&right[2]==color)){
                return d4;
            }else return 0;
        }
        case 2:{
            if((left[1]==empty&&left[2]==color&&left[3]==color)||(right[1]==empty&&right[2]==color&&right[3]==color)){
                return d4;
            }else return 0;
        }
        default:return 0;
    }
}
int alive3(const int *left,const int *right,int length,int color){
    switch(length){
        case 2:{
            if((left[2]==empty&&left[1]==empty&&right[1]==empty&&right[2]==color&&right[3]==empty)||(right[2]==empty&&right[1]==empty&&left[1]==empty&&left[2]==color&&left[3]==empty)){
                return a3;
            }else return 0;
        }
        case 3:{
            if(left[1]==empty&&right[1]==empty&&left[2]==empty&&right[2]==empty){
                return a3;
            }
            else return 0;
        }
        default:return 0;
    }
}
int dead3(const int *left,const int *right,int length,int color){
    int color_;
    color_=get_color_(color);
    switch(length){
        case 1:{
            if((left[1]==color_&&right[1]==empty&&right[2]==color&&right[3]==color)||(right[1]==color_&&left[1]==empty&&left[2]==color&&left[3]==color)||(left[1]==empty&&left[2]==color&&left[3]==empty&&left[4]==color)||(right[1]==empty&&right[2]==color&&right[3]==empty&&right[4]==color)||(left[1]==empty&&right[1]==empty&&left[2]==color&&right[2]==color)){
                return d3;
            }else return 0;
        }
        case 2:{
            if((left[1]==color_&&right[1]==empty&&right[2]==color)||(right[1]==color_&&left[1]==empty&&left[2]==color)||(left[1]==empty&&right[1]==empty&&right[2]==empty&&right[3]==color&&right[4]==color)||(right[1]==empty&&left[1]==empty&&left[2]==empty&&left[3]==color&&left[4]==color)){
                return d3;
            }else return 0;
        }
        case 3:{
            if(left[1]==color_||right[1]==color_||(left[1]==empty&&right[1]==empty&&left[2]==color_&&right[2]==color_)){
                return d3;
            }else return 0;
        }
        default:return 0;
    }
}
int alive2(const int *left,const int *right,int length,int color){
    switch (length){
        case 1:{
            if((left[1]==empty&&right[1]==empty&&right[2]==color&&right[3]==empty)||(right[1]==empty&&left[1]==empty&&left[2]==color&&left[3]==empty)||(left[1]==empty&&right[1]==empty&&right[2]==empty&&right[3]==color)||(right[1]==empty&&left[1]==empty&&left[2]==empty&&left[3]==color)){
                return a2;
            }else return 0;
        }
        case 2:{
            if(left[1]==empty&&right[1]==empty&&(left[2]==empty||right[2]==empty)){
                return a2;
            }else return 0;
        }
        default:return 0;
    }
}
int dead2(const int *left,const int *right,int length,int color){
    int color_;
    color_=get_color_(color);
    switch(length){
        case 1:{
            if((left[1]==color_&&right[1]==empty&&right[2]==color&&right[3]==empty)||(right[1]==color_&&left[1]==empty&&left[2]==color&&left[3]==empty)||(left[1]==color_&&right[1]==empty&&right[2]==empty&&right[3]==color)||(right[1]==color_&&left[1]==empty&&left[2]==empty&&left[3]==color)){
                return d2;
            }else return 0;
        }
        case 2:{
            if((left[1]==color&&right[1]==empty)||(left[1]==empty&&right[1]==color)){
                return d2;
            }else return 0;
        }
        default:return 0;
    }
}