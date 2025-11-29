#include <iostream>
using namespace std;

// 1. Cấu trúc đại diện cho một khách hàng (Node)
struct Node {
    int soVe;           // Số thứ tự/Số vé của khách
    Node* next;         // Con trỏ trỏ tới người tiếp theo
};

// 2. Cấu trúc quản lý Hàng đợi
struct Queue {
    Node* front;        // Người đứng đầu hàng (được phục vụ)
    Node* rear;         // Người đứng cuối hàng (người mới đến sẽ đứng sau người này)
};
// Khởi tạo hàng đợi rỗng
void initQueue(Queue &q) {
    q.front = NULL;
    q.rear = NULL;
}

// Hàm tạo một Node mới (Khách hàng mới lấy vé)
Node* makeNode(int x) {
    Node* newNode = new Node();
    newNode->soVe = x;
    newNode->next = NULL;
    return newNode;
}
void enqueue(Queue &q, int x) {
    Node* newNode = makeNode(x);
    
    // Trường hợp 1: Hàng đang rỗng
    if (q.front == NULL) {
        q.front = q.rear = newNode;
    } 
    // Trường hợp 2: Hàng đã có người
    else {
        q.rear->next = newNode; // Người cuối hiện tại trỏ tới người mới
        q.rear = newNode;       // Cập nhật người mới thành người cuối hàng
    }
    cout << ">> Khách số " << x << " đã xếp hàng.\n";
}
void dequeue(Queue &q) {
    // Kiểm tra nếu hàng rỗng
    if (q.front == NULL) {
        cout << "Hàng đợi rỗng! Không có khách để phục vụ.\n";
        return;
    }

    Node* temp = q.front;       // Lưu người đầu hàng
    cout << ">> Đang phục vụ khách số: " << temp->soVe << "\n";
    
    q.front = q.front->next;    // Người tiếp theo trở thành đầu hàng

    // Nếu sau khi xóa, hàng rỗng thì cập nhật rear
    if (q.front == NULL) {
        q.rear = NULL;
    }

    delete temp; // Xóa người vừa được phục vụ khỏi bộ nhớ
}
// Kiểm tra hàng đợi có rỗng không
bool isEmpty(Queue q) {
    return q.front == NULL;
}

// Xem ai đang đợi ở đầu hàng (nhưng chưa phục vụ ngay)
void peek(Queue q) {
    if (isEmpty(q)) {
        cout << "Hàng đợi đang rỗng.\n";
    } else {
        cout << "Người tiếp theo được phục vụ là khách số: " << q.front->soVe << "\n";
    }
}
void hienThiDanhSach(Queue q) {
    // Bước 1: Kiểm tra rỗng
    if (isEmpty(q)) {
        cout << ">> Hiện tại không có ai xếp hàng!\n";
        return;
    }

    // Bước 2: Dùng biến tạm để duyệt (không được làm mất q.front)
    Node* temp = q.front;
    
    cout << ">> Danh sách đang chờ: ";
    // Bước 3: Vòng lặp duyệt
    while (temp != NULL) {
        cout << "[" << temp->soVe << "] -> "; // In số vé
        temp = temp->next;                    // Nhảy sang người kế tiếp
    }
    cout << "NULL (Hết)\n";
}
int layKichThuoc(Queue q) {
    int count = 0;
    Node* temp = q.front;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int main() {
    Queue q;
    initQueue(q);
  
    int choice, ticketNumber = 1;

    while (true) {
        cout << "\n--- HỆ THỐNG XẾP HÀNG MUA VÉ ---\n";
        cout << "1. Lấy số thứ tự (khách đến)\n";
        cout << "2. Gọi khách vào mua vé (Dequeue)\n";
        cout << "3. Xem người đầu hàng (Peek)\n";
        cout << "4. Kiểm tra tình trạng hàng đợi\n";
        cout << "5. Hiển thị toàn bộ danh sách (Display)\n";
        cout << "6. Đếm số người đang đợi (Size)\n";
        cout << "0. Thoát\n";
        cout << "Nhập lựa chọn: ";
        cin >> choice;

        switch (choice) {
            case 1:
                enqueue(q, ticketNumber++);
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                peek(q);
                break;
            case 4:
                if (isEmpty(q)) cout << "Hàng đợi đang rỗng.\n";
                else cout << "Hiện đang có người xếp hàng.\n";
                break;
            case 5: 
                hienThiDanhSach(q);
                break;
            case 6: 
                cout << ">> Tổng số người đang đợi: " << layKichThuoc(q) << "\n";
                break;
            case 0:
                cout << "Kết thúc chương trình.\n";
                return 0;
            default:
                cout << "Lựa chọn không hợp lệ!\n";
        }
    }
}
