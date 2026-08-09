#include <stdio.h>
#include <string.h>
// Hàm đọc phím
 int doc_phim(int luot_quet) 
 {
    int tin_hieu;
        printf("Lần quét %d, vui lòng nhập số: ", luot_quet);
    scanf("%d", &tin_hieu);
    return tin_hieu;
}
// Hàm so sánh mật khẩu
int so_sanh_mat_khau()


int main()
{ 
    const int CORRECT_PIN[] = {1,0,5,0,8};
    // i là lượt quét
    int i;
    for (i=1;i<=5;i++) 
    {
        // j là tín hiệu
        int j = doc_phim(i);
if (j==99)
    {
        printf("Cảnh báo cạy két\n"); break;
    }
    if (j==-1)
    {
        printf("Lỗi nhiễu điện, bỏ qua!\n");
        i--; continue;
 }
 if (j>=0 && j<=9)
    {
        printf("Đã nhận phím: %d\n",j);
    }
}
printf("Quá trình đọc dữ liệu hoàn tất!");

}
