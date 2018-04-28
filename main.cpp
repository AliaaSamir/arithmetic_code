#include <iostream>
#include <bits/stdc++.h>
using namespace std;

 string sequence,trasmittedCode,setSequense;
 double proba[20],F[20];
 double l=0.0,u=1.0,Tag=0.0,li;
 int n ,data,k=0,seqLength;

int charInSet(char x){
    for(int i=0;i<n;i++){
        if(setSequense[i]== x)
            return i;
    }
    return n-1;
}
void RealValueTag(string transTag){
    double tagVal=0.0;
    for(int i=0;i<k;i++){
        if(transTag[i]=='1'){
            tagVal+=1 / (pow(2,i+1));
        }
        Tag=tagVal;
    }
}
void shiftTag(string &Tag){
    string sub=Tag.substr(1,Tag.length()-1);
    sub+='0';
    Tag=sub;
}

void  getWorkLength(){
    double  mini=abs(F[1]-F[n-1]);;
    double h=1.0;
    for(int i=0;i<n;i++){
        double diff=abs(F[i]-F[i+1]);
        if(mini>diff)
            mini=diff;
    }
   while(mini<h){
    h=1/pow(2,k);
    k++;
   }
    k=k-1;
}

string encoding(string seq){
    int num=seq.length();
    for(int i=0; i<num;i++){
        li=l+(u-l)*F[charInSet(seq[i])];
        u=l+(u-l)*F[charInSet(seq[i])+1];
        l=li;

            while((l>0.0 && l<1.0) && (u>0.0 && u<1.0)){
                if((l>0.0 && l<0.5) && (u>0.0 && u<.5)){
                    l=2*l;
                    u=2*u;
                   trasmittedCode+="0";
                }
                else if((l>.5 && l<=1.0) && (u>.5 && u<=1.0)){
                    l=2*(l-0.5);
                    u=2*(u-0.5);
                    trasmittedCode+="1";
                }

                else
                    break;
            }
    }
    k=trasmittedCode.length();
    RealValueTag(trasmittedCode);
   return trasmittedCode+"1000000000000000";

}



string decode(string trasmittedCode){
    int t;
    double lower,upper;
    string TransTag=trasmittedCode;
    RealValueTag(TransTag);
    while(seqLength--){
            lower=l;
            upper=u;
            for( t=0; t<n ;t++){
                l=lower+(upper-lower)*F[t];
                u=lower+(upper-lower)*F[t+1];
                  //  cout<<l<<" "<<u<<endl;

                if(Tag>l && Tag<u)
                    break;
            }

            sequence+=setSequense[t];
          //  cout<<sequence<<endl;
             while((l>0.0 && l<1.0) && (u>0.0 && u<1.0)){
                if((l>0.0 && l<0.5) && (u>0.0 && u<.5)){
                    l=2*l;
                    u=2*u;
                    shiftTag(TransTag);
                   // cout<<"Transmitted Tag "<<TransTag<<endl;
                    RealValueTag(TransTag);


                }
                else if((l>.5 && l<1.0) && (u>.5 && u<1.0)){
                    l=2*(l-0.5);
                    u=2*(u-0.5);
                    shiftTag(TransTag);
                  //  cout<<"Transmitted Tag "<<TransTag<<endl;
                    RealValueTag(TransTag);

                }

                else
                    break;
             }
    }
    return sequence;

}

int main()
{
    int choice;
    cout<<"if you want to encode click <1> decode <2>"<<endl;
    cin>>choice;
    if(choice == 1){
            cout << "Enter the set of sequence" << endl;
            cin>>setSequense;
            cout << "Enter the sequence" << endl;
            cin>>sequence;
            n=setSequense.length();
            cout << "Enter the probabilities" << endl;
            F[0]=0;
            for(int i=1;i<n+1;i++){
                cin>>proba[i];
                F[i]=proba[i]+F[i-1];
            }

            cout<< encoding(sequence)<<endl;
            cout<< Tag<<endl;
                    }
    else
    {
        cout << "Enter the set of sequence" << endl;
        cin>>setSequense;
        cout << "Enter the transmittedCode" << endl;
        cin>>trasmittedCode;
        n=setSequense.length();
        cout << "Enter the FunctionsValue" << endl;
            F[0]=0;
            for(int i=1;i<n+1;i++){
                cin>>F[i];
            }
        cout << "Enter sequence length" << endl;
        cin>>seqLength;
            getWorkLength();
        cout<< decode(trasmittedCode)<<endl;
    }

    return 0;
}
