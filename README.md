#include <stdio.h>
#include <stdbool.h>
// Hàm đọc phím
 int doc_phim(int luot_quet) 
 {
    int tin_hieu;
        printf("Lần quét %d, vui lòng nhập số: ", luot_quet);
    scanf("%d", &tin_hieu);
    return tin_hieu;
}
// Hàm so sánh mật khẩu
bool so_sanh_mat_khau(int so_duoc_nhap[], const int so_dung[], int do_dai)
{
    bool hop_le = true;
    int k;
    for(k=0 ; k < do_dai ; k++)
    {
        if(so_duoc_nhap[k] != so_dung[k]) 
        {
            hop_le = false;
        }
    }
return hop_le;
}

int main()
{ 
    const int CORRECT_PIN[] = {1,0,5,0,8};
    int user_input[5];
    // i là lượt quét
    int i;
    for (i=1;i<=5;i++) 
    {
        // j là tín hiệu
        int j = doc_phim(i);
if (j==99)
    {
        printf("Cảnh báo cạy két !\n"); return 0;
    }
    if (j==-1)
    {
        printf("Lỗi nhiễu điện, bỏ qua\n");
        i--; continue;
 }
 if (j>=0 && j<=9)
    {
        printf("Đã nhận phím: %d\n",j);
        user_input[i-1] = j;
    }
     else { 
      printf("Phím không hợp lệ, vui lòng thử lại\n");
      i--;
     }
    }
if (so_sanh_mat_khau(user_input , CORRECT_PIN , 5))
{
    printf("Mở khóa thành công !\n");
}
else { printf("Sai mật khẩu, hãy thử lại !\n"); }
}
