#define NO_INLINE __attribute__((noinline))
#define SLEEP for(volatile int i=0;i<100000;i++){};

void NO_INLINE foo_x(){  
    SLEEP;               
}
void NO_INLINE foo_a(){  
    SLEEP;               
}
void NO_INLINE foo_b(){  
    SLEEP;               
}
void NO_INLINE foo_c(){ 
    foo_x(); 
    SLEEP;               
}
void NO_INLINE foo_d(){  
    foo_x();
    foo_x();
    SLEEP;               
}

int main(){
    long long int count = 10000;
    while (count--){
        foo_b();
        SLEEP;

        foo_a();
        SLEEP;

        foo_b();
        SLEEP;

        foo_c();
        SLEEP;
        
        foo_d();
        SLEEP;
    }
    SLEEP;
    return 0;
}

