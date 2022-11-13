#include <bits/stdc++.h>
#include <fstream>
using namespace std;
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define ll long long int
#define ld long double  
#define in insert
#define pb push_back 
#define vll vector<ll>
#define vpll vector<pair<ll,ll>>
#define pll pair<ll,ll>
#define mll map<ll,ll>
#define umll unordered_map<ll,ll>
#define vpll vector<pair<ll,ll>> 
#define sll set<ll>
#define mcl map<char,ll>
#define mlc map<ll,char>
#define msll multiset<ll>
#define b32 bitset<32>
ll power_2(ll n){
   ll count=0;
   ll k=n;
   while(k%2==0){
    k=k/2;
    count++;
   }
   return count;
}

ld hit;
ld hitr;
ld hitw;
ll rc;
ll wc;
ll cache_size;
ll cache_block_size;
ll no_of_bits_in_adress;
ll no_of_ways;
vector<pair<char,string>> inp;

int main(){
    fast_io;
    unordered_map<char,string> m;
    m['0']="0000";
    m['1']="0001";
    m['2']="0010";
    m['3']="0011";
    m['4']="0100";
    m['5']="0101";
    m['6']="0110";
    m['7']="0111";
    m['8']="1000";
    m['9']="1001";
    m['a']="1010";
    m['b']="1011";
    m['c']="1100";
    m['d']="1101";
    m['e']="1110";
    m['f']="1111";
    ifstream myfile("input1.txt");
    string hex;
    while(myfile){
      getline(myfile,hex);
         ll siz=hex.size();
         string out="";
         char id=hex[1];
         for(ll i=2;i<siz;i++){
            out+=m[hex[i]];
         }
         inp.pb({id,out});
    }
    hit=0;
   cin>>cache_block_size>>cache_size>>no_of_ways;
   no_of_bits_in_adress=inp[0].second.size();
   ll cs,cbs,ab,w;
   cs=cache_size;
   cbs=cache_block_size;
   ab=no_of_bits_in_adress;
   w=no_of_ways;
   if((cs!=(ll)pow(2,power_2(cs)))||(cbs!=(ll)pow(2,power_2(cbs)))||(w!=(ll)pow(2,power_2(w)))){
      cout<<"Enter Power of 2 as input"<<"\n";
      return 0;
   }
   else if(cs<cbs){
      cout<<"Enter Valid values for Cache size and Cache block size"<<"\n";
      return 0;
   }
   ll total_blocks=cache_size/cache_block_size;
   if(total_blocks<w) {
      cout<<"Enter Valid Number of Ways"<<"\n";
      return 0;
   }
   ll blocks_per_set=total_blocks/no_of_ways;
   ll no_of_ofset_bits=power_2(cache_block_size);
   ll no_of_index_bits=power_2(blocks_per_set);
   ll no_of_tag_bits=no_of_bits_in_adress-no_of_index_bits-no_of_ofset_bits;   
   vector<pair<string,ll> > v[w];
   pair<string,ll> p={"-1",-1};
   for(ll i=0;i<w;i++){
   for(ll j=0;j<blocks_per_set;j++){
      v[i].pb(p);
         }
      }
      ll max_value_of_adress=1;
      for(ll i=0;i<=no_of_bits_in_adress;i++){
         max_value_of_adress*=2;
      }
      ll number_of_inputs=inp.size();
      ll c=number_of_inputs;
      while(number_of_inputs--){
         string nu=inp[number_of_inputs].second;
         ll r=0,w=0;
         if(inp[number_of_inputs].first=='1') {
            r=1;
            rc++;
         }
         else {
         w=1;
         wc++;
      }
         b32 addr(nu);
         ll num=addr.to_ulong();

         ll index=(num%(cache_size/no_of_ways))/cache_block_size;
         ll starting_index_of_adress=32-no_of_bits_in_adress;
         string tag=addr.to_string().substr(starting_index_of_adress,no_of_tag_bits);
         bool rh=false; //read hit;
         for(ll i=0;i<no_of_ways;i++){
               if(tag==v[i][index].first){
                     v[i][index].second=1;
                     if(r==1 && w==0){
                        hitr++;
                     }
                     else {
                        hitw++;
                     }
                     hit++;
                     rh=true;
               }
               else {
                  if(v[i][index].second!=-1);
                  v[i][index].second++;
               }
         }
         if(!rh){
            ll max=0;
            ll ind;
            bool empty_block=false;
            for(ll i=0;i<no_of_ways;i++){
               if(v[i][index].first=="-1"){
                  v[i][index].first=tag;
                  v[i][index].second=1;
                  empty_block=true;
                  break;
               }
               if(v[i][index].second>max) {
                     ind=i;
                     max=v[i][index].second;
               }
            }
            if(!empty_block){
               v[ind][index].first=tag;
               v[ind][index].second=1;
            }
         }
      }
      cout<<setprecision(20);
      cout<<"Number of Inputs : "<<c<<"\n";
      cout<<"Number of hits : "<<hit<<"\n";
      cout<<"Number of misses : "<<c-hit<<"\n";
      hit=hit/c;
      cout<<"Hit percentage: "<<hit*100<<"\n";
      cout<<"Number of read Inputs : "<<rc<<"\n";
      cout<<"Number of read hits : "<<hitr<<"\n";
      cout<<"Number of read misses : "<<rc-hitr<<"\n";
      hitr=hitr/rc;
      cout<<"Hit percentage of read : "<<hitr*100<<"\n";
      cout<<"Number of write  Inputs : "<<wc<<"\n";
      cout<<"Number of write hits : "<<hitw<<"\n";
      cout<<"Number of write misses : "<<wc-hitw<<"\n";
      hitw=hitw/wc;
      cout<<"Hit percentage of write: "<<hitw*100<<"\n";


    return 0;
} 