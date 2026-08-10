#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
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
// Hàm đếm sai và tạm khóa
bool kiem_tra_lan_sai(bool hop_le , int *so_lan_sai)
{
if (hop_le) 
{ 
    printf("Mở khóa thành công\n");
    *so_lan_sai = 0;
    return false;
}
else { 
    (*so_lan_sai)++;
    int luot_con_lai = 3 - *so_lan_sai;
    printf("Bạn đã nhập sai %d lần, còn lại: %d\n", *so_lan_sai, luot_con_lai);
}
if (*so_lan_sai >= 3)
{
    printf("Mở khóa thất bại, vui lòng chờ...\n");
    int sec;
    for (sec = 60 ; sec > 0 ; sec--)
    {
        printf("Vui lòng chờ %d giây để thử lại\n", sec);
        Sleep(1000);
}
 *so_lan_sai = 0;
    return false;
}
return false; // trạng thái mặc định của két
}
// Hàm báo lỗi 
void phat_canh_bao(int ma_loi)
{
switch (ma_loi)
{
    case 1:
printf("---Cảnh báo cạy két !---\n");
break;
case 2: 
printf("---Lỗi nhiễu điện, bỏ qua---\n");
break;
case 3: 
printf("---Phím không hợp lệ, vui lòng thử lại---\n");
break;
}
}
int main()
{ 
    int CORRECT_PIN[] = {1,0,5,0,8}; // mật khẩu két sắt (có thể thay đổi)
    int user_input[5]; // giá trị người dùng nhập
    int so_lan_sai = 0;
    while (1)
    {
        // i là lượt quét
    int i;
    printf("---Vui lòng nhập mật khẩu---\n");
    for (i=1;i<=5;i++) 
    {
        // j là tín hiệu
        int j = doc_phim(i);
if (j==99)
    {
      phat_canh_bao(1);
      return 0;
    }
    if (j==-1)
    {
     phat_canh_bao(2);
        i--; continue;
 }
 if (j>=0 && j<=9)
    {
        printf("Đã nhận phím: %d\n",j);
        user_input[i-1] = j;
    }
     else { 
      phat_canh_bao(3);
      i--;
     }
    }
bool hop_le = so_sanh_mat_khau(user_input , CORRECT_PIN , 5);
bool bi_khoa = kiem_tra_lan_sai(hop_le , &so_lan_sai);
if (bi_khoa || hop_le)
{
break;
}
}
return 0;
}
