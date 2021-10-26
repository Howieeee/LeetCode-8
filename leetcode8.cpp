class Solution {
public:
    
    int cal_ans(string &num,int &sign){
        int ans=0;

        for(int i=num.size()-1,j=0;i>=0;i--,j++)
            ans += (num[j]-'0')*pow(10,i);
        

        ans = ans*sign;
        
        return ans;
    }
    
    bool out_of_range(string num, int &sign ,string max, string min){
        if(num.size() > 10)
            return true;
        string compare_str = (sign == 1) ? max : min;
        

        for(int i=0;i<num.size();i++){
            if(num[i] > compare_str[i])
                return true;
            if(num[i] < compare_str[i])
                return false;
        }
        return true;
    }
    
    int myAtoi(string s) {
        string max = "2147483647" , min = "2147483648";  //min的負號不看
        char space = ' ';
        char negative = '-';
        char positive = '+';
        int sign = 1;
        string str;
        bool sign_detected =false;
        bool end = false;
        bool digit_detected = false;
        bool else_detected = false;
        bool except_zero = false;
        for(auto ch:s){
            
            if(end)
                break;
            
            if(ch == space){
                
                if( (sign_detected || else_detected) && !digit_detected )
                    return 0;                
                if(digit_detected)
                    end =true;
                
            }else if(ch == positive || ch == negative ){
                
                if(digit_detected)//之前有偵測到數字
                    end = true;//可以結束
                
                if(sign_detected && !digit_detected)//再次讀到
                    return 0;
                
                sign_detected = true;//偵測到sign
                
                if(ch == negative && !digit_detected)//負的 
                    sign = -1;
                
            }else if( ch-0>=48 && ch-0 <=57 && !end){
                
                if(else_detected && !digit_detected){
                    end = true;
                    break;
                }
                
                if(ch == '0'){ //偵測到0
                    if(except_zero) //有0以外的
                        str+= ch;
                    
                }else{
                    except_zero = true;
                    str += ch;
                }
                
                digit_detected = true; //第一次偵測到數字
                
            }else{
                if(digit_detected)
                    end = true;
                else_detected =true;
            }
        }
        int ans = 0 ;
        //cout << str.size();
        if(str.size() >= 10){ //>10 =10 超過範圍的
            //cout << out_of_range(str,sign,max,min) << endl;
            if(out_of_range(str,sign,max,min)){ //超出範圍
                //cout << sign ;
                
                if(sign == 1)
                    return numeric_limits<int>::max();
                else
                    return numeric_limits<int>::min();
                
            }
        }
        
       ans = cal_ans(str,sign);
        
        
        return ans;
        
    }
};
