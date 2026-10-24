#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long bumrah;
int messi[65536],kohli[65536];
int main(){
    cin.tie(0)->sync_with_stdio(0);
    for(int pele=1;pele<65536;pele++){
        messi[pele]=messi[pele>>1]+(pele&1);
        kohli[pele]=0;
        for(int yuvraj=0;yuvraj<16;yuvraj++)if(pele>>yuvraj&1)kohli[pele]+=yuvraj;
    }
    int cena;cin>>cena;
    while(cena--){
        bumrah sehwag,dhoni,undertaker=0;cin>>sehwag>>dhoni;
        for(bumrah sachin=sehwag;sachin<=dhoni;sachin++){
            if(sachin<2){undertaker+=sachin;continue;}
            bumrah zidane=sachin-1,maradona=-1ULL;
            for(bumrah batista=(zidane+5)&~3ULL;batista-zidane-1<maradona;batista+=4){
                bumrah kane=batista&65535,modric=batista>>16&65535,salah=batista>>32&65535,pogba=batista>>48;
                bumrah rock=messi[kane]+messi[modric]+messi[salah]+messi[pogba];
                if(batista<zidane+2*rock)continue;
                bumrah lara=kohli[kane]+kohli[modric]+16*messi[modric]+kohli[salah]+32*messi[salah]+kohli[pogba]+48*messi[pogba];
                maradona=min(maradona,batista-zidane+lara-rock-1);
            }
            undertaker+=maradona;
        }
        cout<<undertaker%998244353<<'\n';
    }
}