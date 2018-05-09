//////////////////////////////////
// liberay include here:
#include <oled-exp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ugpio/ugpio.h>
#include <ctime>
/////////////////////////////////////////////
using namespace std;
///////////settime time the alarm clock/////////

int setTime( float& value)
{
    char input[5];
    cout << " Please set a time: " << endl;
    cin >> input;
    
    //error check: empty input
	//return to the function one more time instead of false!////
    if (input[0] == '\0')
    {
        cerr << "Invalid Time" << endl;
        return setTime(value);
    }
    
    // determine the length of the input
    int size = 0;
    while (input[size] != '\0' && input[size] != 0)
        size++;
    
    //the input should be the form 00:00, therefore,
    //the maximum characters in this input is 5.
    if ( size > 5 )
    {
        cerr << "Invalid Time" << endl;
        return setTime(value);
    }
    
    //convert the input to number
    //convert hour
    int hour = 0;
    int minute = 0;
    int i = 0;
    for (i = 0; input[i] != ':'; i++)
    {
        if ( input[i] > '9' && input[i] < '0')
        {
            cerr <<"Invalid Time" << endl;
            return setTime(value);
        }
        else
        {
            hour = hour*10 + input[i] - '0';
        }
    }
    
    i++;
    
    //convert minute
/////////// use the same method as hours previously////////////
    for (; input[i] != '\0'; i++)
    {
        if ( input[i] > '9' || input[i] < '0')
        {
            cerr <<"Invalid Time" << endl;
            return setTime(value);
        }
        else
        {
            minute = minute*10 + input[i] - '0';
        }
    }
    
    //error check:
    //hour cannot exceed 24
    //minute cannot exceed 60
	// if so return the function instead of false!!!!!!!!!!!!
	//do not show anything on OLED screen//////////
    if (hour > 24 || minute > 60)
        return setTime(value);
    
    struct tm *Time;
    time_t localTime;
    localTime = time(NULL);
    Time = localtime(&localTime);
    //////initial the variable that whose value output on the screen
    float minuteLeft=0;
    float secondLeft=0;
   /////////////calculation
    float hourLeft = hour - Time->tm_hour-1;
    if (hourLeft>=0)
	{
        minuteLeft =60+minute  - Time->tm_min;
        secondLeft = hourLeft*3600 + minuteLeft*60;
    }
	
	
    else
	{
        hourLeft=hourLeft+24;
        minuteLeft =60+minute  - Time->tm_min;
        secondLeft = hourLeft*3600 + minuteLeft*60;    
    }
//////////calculation part finished..	
	
/////////pay attention here:
/////////this is output to the computer console, 
////////////////not the OLED(haven't connected yet)//////////

    cout << "hourLeft is : " << hourLeft << endl;
    cout << "minuteLeft is : " << minuteLeft << endl;
    cout << "secondLeft is : " << fabs(secondLeft) << endl;
    // cout current time
    return fabs(secondLeft);
}
//music parameters (used later in the playMusic	function fo buzzer)///////////////////////////
////////////////initial for do ri mi etc//////////////
int Do();
int Re();
int Mi();
int Fa();
int So();
int La();
int Xi();
int playMusic();
// x is frequency*2;
// usleep value is 1/f  (T);
/////////////function that change frequency for do////////
/////////////do only run 1 sec when using buzzer////////////
int Do()
{
    int rs;
    int x = 0;
	
    while(x <= 52) 
	{
        rs = gpio_request(1, NULL);
        rs = gpio_direction_output(1, 1);
        usleep(3816);
        rs = gpio_direction_output(1, 0);
        usleep(3816);
        x++;
    }
    return 0;
}

/////////////function that change frequency for re////////
/////////////re only run 1 sec when using buzzer////////////
int Re()
{
    int rs;
    int x = 0;
    while(x <= 58) 
	{
        rs = gpio_request(1, NULL);
        rs = gpio_direction_output(1, 1);
        usleep(3401);
        rs = gpio_direction_output(1, 0);
        usleep(3401);
        x++;
    }
    return 0;
}
/////////////function that change frequency for mi, fa so ,la, xi////////
int Mi()
{
    int rs;
    int x = 0;
    
    while(x <= 66) 
	{
        rs = gpio_request(1, NULL);
        rs = gpio_direction_output(1, 1);
        usleep(3030);
        rs = gpio_direction_output(1, 0);
        usleep(3030);
        x++;
    }
    return 0;
}


int Fa()
{
    int rs;
    int x = 0;
    while(x <= 69) {
        rs = gpio_request(1, NULL);
        rs = gpio_direction_output(1, 1);
        usleep(2865);
        rs = gpio_direction_output(1, 0);
        usleep(2865);
        x++;
    }
    return 0;
}

int So(){
    int rs;
    int x = 0;
    while(x <= 78) 
	{
        rs = gpio_request(1, NULL);
        rs = gpio_direction_output(1, 1);
        usleep(2551);
		
		
        rs = gpio_direction_output(1, 0);
        usleep(2551);
        x++;
    }
}


int La(){
    int rs;
    int x = 0;
	
    while(x <= 88) 
	{
        rs = gpio_request(1, NULL);
        rs = gpio_direction_output(1, 1);
        usleep(2273);
        rs = gpio_direction_output(1, 0);
        usleep(2273);
        x++;
    }
    return 0;
}

int Xi()
{
    int rs;
    int x = 0;
	
    while(x <= 98) {
        rs = gpio_request(1, NULL);
        rs = gpio_direction_output(1, 1);
        usleep(2024);
        rs = gpio_direction_output(1, 0);
        usleep(2024);
        x++;
    }
    return 0;
}

int playMusic(){
    // connect this while condition to the timer funciton later on
        Do();
        Do();
        So();
        So();
        La();
        La();
        So();
        Fa();
        Fa();
        Mi();
        Mi();
        Re();
        Re();
        Do();
        So();
        So();
        Fa();
        Fa();
        Mi();
        Mi();
        Re();
    return 0;
}


///date and time /////////////////////////////////
void addition(char *a, char *b)
{
    int i = 0;
    while (a[i] != '\0')
        i++;
    for (int count = 0; b[count] != '\0'; count++)
	{
        a[i] = b[count];
        i++;
    }
};
///////////////////following function are component of the class 
//////////////////that defined in line 262//////////////////

class changeTimeFormat
{
public:
    char* changeTimeFormatOfTheDay();
    void itoa(int num,char * pstr);
    char* getCurrentTime();
     
private:
    
};



void changeTimeFormat::itoa(int num, char *pstr) 
{
    int i = 11;
    char str[i+2];
    str[i+1] = '\0';
	
    while(num>9){
        str[i--] = '0' + num%10;
        num /= 10;
    }
	
    str[i] = num+'0';
    strcpy(pstr,&(str[i]));
}

/**Extract the date from the system, transferring it to the formal time format
 @return an array of char which stores the time*/
 
 
char* changeTimeFormat::changeTimeFormatOfTheDay() 
{
	
    struct tm *timeNow;
    time_t currentTime;
    currentTime = time(NULL);
    timeNow = localtime(&currentTime);
    
    int t = timeNow->tm_mday;
    char day[5] = {'\0'};
    
    itoa(timeNow->tm_mday, day);
    ////////////different value of t leads to different date
    if (t == 1) 
	{
        day[0] = '1';
        day[1] = 's';
        day[2] = 't';
        day[3] = '\0';
    }
	
    else if (t == 2)
	{
        day[0] = '2';
        day[1] = 'n';
        day[2] = 'd';
		
        day[3] = '\0';
    }
	
    else if (t == 3)
	{
        day[0] = '3';
        day[1] = 'r';
        day[2] = 'd';
		
        day[3] = '\0';
    }
	
    else if (t == 21) 
	{
        day[0] = '2';
        day[1] = '1';
        day[2] = 's';
        day[3] = 't';
        day[4] = '\0';
    }
	
    else if (t == 22){
        day[0] = '2';
        day[1] = '2';
        day[2] = 'n';
        day[3] = 'd';
		
        day[2] = '\0';
    }
    else if (t == 23)
	{
        day[0] = '2';
        day[1] = '3';
        day[2] = 'r';
        day[3] = 'd';
        day[4] = '\0';
    }
	
    else {
        int i = 0;
        while (day[i+1] != '\0')
            i++;
		
        day[i+1] = 't';
        day[i+2] = 'h';
		
        day[i+3] = '\0';
    }
    
    char *store[] = {"January", "February", "March",
	"April", "May", "June", "July", "August", "September", 
	"October", "November", "December"};
    
    char *month = store[timeNow->tm_mon];
    char *sendTime = new char[100];
	/////////////
	/////////first inital sendtime all to zero
    for (int i = 0; i < 100; i++)
		
        sendTime[i] = '\0';
    
    char year[5] = {'\0'};
    
    itoa((timeNow->tm_year + 1900), year);
    
    addition(sendTime, day);
	
    addition(sendTime, ", ");
    
	addition(sendTime, month);
    
	addition(sendTime, ", ");
    
	addition(sendTime, year);
    
    return sendTime;
}


/**Get the exact time precised to seconds and transferring it to the formal time format
 @return an array of char which stores the exact time*/
 
char* changeTimeFormat::getCurrentTime() {
	
	
    //define a function which can appendix array of char
    //find the time of the local zone
    struct tm *timeNow;
    time_t currentTime;
    currentTime = time(NULL);
    timeNow = localtime(&currentTime);
    
    char hour[3] = {'\0'};
    char minute[3] = {'\0'};
    char second[3] = {'\0'};
    char* localTime = new char[40];
    for (int i = 0; i < 40; i++)
        localTime[i] = {'\0'};
    
    
    //    cout << timeNow->tm_hour << endl;
    itoa(timeNow->tm_hour, hour);
	
    itoa(timeNow->tm_min, minute);
    
	itoa(timeNow->tm_sec, second);
    
	
	

    addition(localTime, "   ");
    
	addition(localTime, hour);
    
	addition(localTime, " : ");
    
	addition(localTime, minute);
    
	addition(localTime, " : ");
    
	addition(localTime, second);
    
    return localTime;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Time{
public:
    int min;
    int sec;
public:
    Time(int b,int c)
    {
        min=b;
        sec=c;
    }
    void show()
    {
        cout << '\r';
        
        
        if(min<10)
            cout << 0 << ':';
        cout << min << ':';
        if(sec<10)
            cout << 0;
        cout << sec << flush;        
    }
	
	
    void tick()
    {
        long t=time(NULL);
        while(time(NULL)== t);
		
        if(--sec <= 0 && min > 0)
        {
            min=min-1;
            sec=59;       
        }
    }
	
	
	
    void run()
    {
		tick();
        show();
		
		if(sec <= 5 && min == 0) 
		{
		playMusic();
		min = 99;
		}
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() 
{
	
//////first of all,  call for the countdown function and
    changeTimeFormat t;
    Time countDown(0,10);
    float countdowntime = 0;
///////call settime function and consider counterdowntime as the input
    setTime(countdowntime)
    Time clock(0,countdowntime);
    bool flag = false;
    bool innerFlag = false;
    int rs;
	
    rs = gpio_request(0, NULL);
    rs = gpio_get_value(0);
	
    int status = oledDriverInit();
    status = oledSetDisplayPower(1);

	
	
    while(1) 
	{  
        char *a = new char[30];
        for (int i = 0; i < 10; i++)
            a[i]='\0';
        char b[5] = {'\0'};
        char c[5] = {'\0'};
        
		t.itoa(countDown.min, b);
        t.itoa(countDown.sec, c);
        
		addition(a, b);
        addition(a, " : ");
        addition(a, c);
        
		
        char *d = new char[30];
        for (int i = 0; i < 10; i++)
            d[i]='\0';
        char e[5] = {'\0'};
        char f[5] = {'\0'};
        t.itoa(countDown.min, e);
        t.itoa(countDown.sec, f);
		addition(d, e);
        addition(d, " : ");
        addition(d, f);
        
		
        status = oledSetCursorByPixel(1, 63);
		
        status =  oledWrite(t.getCurrentTime());
        
		status = oledSetCursorByPixel(2, 63);
        
		status =  oledWrite(t.changeTimeFormatOfTheDay());

        status = oledSetCursorByPixel(3, 63);
        
		status = oledWrite(a);
       
        status = oledSetCursorByPixel(4, 63);
        status = oledWrite(d);
		
		
        ////////////flag is used////////
		//////////checking circuite: ///////////
		/////false when gpio is wrong, true when it is working///////
		
        if (countDown.min<=10)
		{
            rs = gpio_get_value(0);
            if(gpio_get_value(0) == true)
			{
                flag = true;}
            
            while (gpio_get_value(0) == true && flag == true)
	////////////////just do nothing////////////
			{;}
            
            if(flag == true && gpio_get_value(0) == false) 
			{
                flag = false;
                countDown.min++;
            }
        }
        
        if(countDown.min > 10)
		{
            countDown.min = 99;
            if(countDown.min > 15 && gpio_get_value(0) == true)
                innerFlag = true;
			
            while (gpio_get_value(0) == true && innerFlag == true){;}
			
            if(innerFlag == true && gpio_get_value(0) == false) 
			{
                countDown.min = 1;
                innerFlag = false;
            }
        }
            
        countDown.run();
        countdowntime.run();
		
        if (countdowntime.second < 5 && countdowntime.minute == 0)
		{
            playMusic;
            countdowntime.minute = 99999;
        }

    }
 
    return 0;
}
