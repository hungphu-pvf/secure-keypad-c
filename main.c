#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
typedef enum 
{ //Trạng thái có thể xảy ra
    OTP_SUCCESS,
    OTP_WRONG,
    OTP_TIMEOUT
} OTP_RESULT;
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
// Hàm tạo OTP
int otp()
{
    return 1000 + rand() % 9000;
}
// Hàm kiểm tra OTP và thời gian
int kiemtra_otp(int otp_nhap , int otp_goc , time_t start_time)
{
   time_t hien_tai = time(NULL);
   double thoi_gian = difftime(hien_tai , start_time);
   if (thoi_gian > 600)
   {
    printf("---Đã hết giờ nhập mã---\n");
    return OTP_TIMEOUT;
   }
if (otp_goc == otp_nhap)
{
    printf("---OTP đúng---\n");
    return OTP_SUCCESS;
}
else if (otp_goc != otp_nhap)
{
    printf("---OTP sai---\n");
    return OTP_WRONG;
}
}

// Hàm báo lỗi 
void phat_canh_bao(int ma_loi)
{
switch (ma_loi)
{
    case 1:
printf("---Cảnh báo cạy két, hệ thống sẽ bị khóa 6 tiếng !---\n");
sleep(60*60*6);
break;
case 2: 
printf("---Lỗi nhiễu điện, bỏ qua---\n");
break;
case 3: 
printf("---Phím không hợp lệ, vui lòng thử lại---\n");
break;
}
}
// Hàm lưu mật khẩu vào file
void save_pin(int pin[] , int do_dai)
{
    FILE *f = fopen("pin.txt" , "w"); //mở file để ghi đè mật khẩu lên
    if (f != NULL)
    {
for (int k = 0 ; k < do_dai ; k++)
{
    fprintf(f , "%d ", pin[k]);
}
    fclose(f);
    }
}
void load_pin(int pin[] , int do_dai)
{
    FILE *f = fopen("pin.txt" , "r"); //mở file để đọc
    if (f==NULL)
    {
        int default_pin[] = {1,2,8,1,5};
        for (int k = 0 ; k < do_dai ; k++)
        {
            pin[k] = default_pin[k];
        }
        save_pin(pin , do_dai);
        return;
    }
        for (int k = 0 ; k < do_dai ; k++)
        {
            fscanf(f , "%d ", &pin[k]);
        }
        fclose(f);
    }
// Hàm đổi mật khẩu
void doi_mat_khau(int mat_khau_hien_tai[] , int do_dai)
{
    int lua_chon;
     int so_moi[5];
     int xac_nhan[5];
      int k;
   printf("---Bạn có muốn đổi mật khẩu không ? (1:Có , 0: Bỏ qua)---\n");
   scanf("%d", &lua_chon);
   switch (lua_chon)
   {
    case 0:
    break;

    case 1:
    printf("Vui lòng nhập mật khẩu mới %d chữ số\n" , do_dai);
    for (k = 0 ; k < do_dai ; k++)
    {
        printf("Nhập số thứ %d: ", k+1);
        scanf("%d", &so_moi[k]);
   }
    //Kiểm tra lần 2 coi khớp không
    printf("---Vui lòng xác nhận lại mật khẩu mới---\n");
    for (k = 0 ; k < do_dai ; k++)
    {
        printf("Nhập số thứ %d: ", k+1);
        scanf("%d", &xac_nhan[k]);
    }
    if(so_sanh_mat_khau(so_moi , xac_nhan , do_dai))
    {
        for (k = 0 ; k < do_dai ; k++)
        {
            mat_khau_hien_tai[k] = so_moi[k];
        }
        save_pin(mat_khau_hien_tai , do_dai);
        printf("---Lưu mật khẩu mới thành công !---\n");
    }
    else {
        printf("---Mật khẩu xác nhận không khớp, đổi mật khẩu thất bại---\n");
    }
    break;
default:
printf("---Giữ nguyên mật khẩu cũ---\n");
    }
}
int main()
{   
    srand(time(NULL));  //Để cho OTP luôn ngẫu nhiên
    int CORRECT_PIN[] = {1,2,8,1,5}; // mật khẩu két sắt (có thể thay đổi)
    load_pin(CORRECT_PIN , 5);
    int user_input[5]; // giá trị người dùng nhập
    int so_lan_sai = 0;
    int otp_lan_sai = 0;
    bool mo_khoa_thanh_cong = false;
    while (1)
    {
        bool cay_ket = false;
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
      cay_ket = true;
      break;
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
    if (cay_ket)
{
    continue;
}
bool hop_le = so_sanh_mat_khau(user_input , CORRECT_PIN , 5);
memset(user_input , 0 , sizeof(user_input));
if (hop_le) 
{ 
    printf("---Mở khóa thành công---\n");
    so_lan_sai = 0;
    doi_mat_khau(CORRECT_PIN , 5);
    break;
}
else { 
    so_lan_sai++;
    int luot_con_lai = 3 - so_lan_sai;
    printf("Bạn đã nhập sai %d lần, còn lại: %d\n", so_lan_sai, luot_con_lai);
}
if (so_lan_sai >= 3)
{
    time_t start_time = time(NULL);
    int otp_nhap;
    int otp_gui = otp();
    // otp_gui == otp_goc
printf("---Nhập sai mật khẩu quá 3 lần---\n");
printf("---Mã OTP để mở khóa sẽ được gửi qua SMS của bạn---\n");
printf("---Mã OTP của bạn là: %d\n", otp_gui); //truyền tin thông qua SMS
bool exit_otp = false;
while (!exit_otp)
{
printf("---Vui lòng nhập mã (4 chữ số)---\n");
scanf("%d", &otp_nhap);
OTP_RESULT ket_qua = kiemtra_otp(otp_nhap , otp_gui , start_time);
if (ket_qua == OTP_SUCCESS)
{
    printf("---Xác thực thành công---\n");
    so_lan_sai = 0;
    otp_lan_sai = 0;
    doi_mat_khau(CORRECT_PIN , 5);
    mo_khoa_thanh_cong = true;
    break;
}
else if (ket_qua == OTP_WRONG)
{
    otp_lan_sai++;
    printf("---Sai OTP, vui lòng thử lại---\n");
if (otp_lan_sai >= 5)
{
    printf("---Nhập sai OTP quá 5 lần, tiến hành khóa 6 tiếng---\n");
    sleep(60*60*6);
    so_lan_sai = 0;
    otp_lan_sai = 0;
    break;
}
}
if (ket_qua == OTP_TIMEOUT)
{
    printf("---Quá thời gian, hệ thống sẽ bị khóa 6 tiếng---\n");
    sleep(60*60*6);
    so_lan_sai = 0;
    otp_lan_sai = 0;
    break;
}
}
if (mo_khoa_thanh_cong)
{
    break;
}
}
    }
}
