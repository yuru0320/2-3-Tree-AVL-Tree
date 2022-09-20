# 2-3-Tree-AVL-Tree

# 開發平台
Window 10

# 開發環境
Dev-C++ 5.11

# 說明
以入學資料作為數據，分別建立 2-3 樹及 AVL 樹，並顯示其樹高和根節點內所儲存的學校資訊。

# input檔案格式
前3列為標題。

第4列開始每行依序為[學校代碼][學校名稱][科系代碼][科系名稱][日間∕進修別][等級別][學生數][教師數][上學年度畢業生數][縣市名稱][體系別]，不同欄位之間以"tab"隔開。

# 使用流程
1.編譯與執行。

2.螢幕會顯示提示字元:「Input a choice(0,1) :」，優先選擇輸入：1 ( 1.Build 2-3 tree )，若先選擇2 ( 2.Build AVL tree )，則會顯示「###Choose 1 first.###」，輸入0則會結束執行。

3.輸入檔名( ex:input201 )，若檔案不存在則會顯示「###檔名does not exist###」，並且需要重新輸入檔名，直至檔名正確。

4.若輸入正確檔案名稱，則會顯示2-3 tree之樹高、樹根節點所儲存的學校資訊、節點總數、學校數量。

5.選擇是否執行mission 2( Build AVL tree )。

6.若選擇輸入2，則會顯示AVL tree之樹高、樹根節點所儲存的學校資訊、節點總數、學校數量。

# 簡介
#### 2-3 tree
是一種平衡的樹狀結構(Balance)，這個資料結構是由下而上長的樹，且能確定每個leaf的樹高都是相同的。

每個節點最多放兩個key ，也就是說每個節點最多會有3個子樹。

先將資料讀進，再一筆一筆依照插入樹中2-3樹的概念。

#### AVL tree
每新增一個節點就將其父節點紀錄，並且檢查其平衡係數是否需要做交換(RR、LL、LR、RL)，再計算樹高，最後將其樹高、head節點印出。

檢查其平衡係數: 將此節點的父節點作為基準點，計算左右分支個別數高，左樹高減右樹高後，作為第一個平衡係數，在將此節點的祖父節點作為基準點，也計算左右數高，左樹高減右樹高後，作為第二個平衡係數。

RR: 先將暫存的節點設為目前節點的右節點，再將目前節點的右節點設為暫存節點的左節點，再將暫存節點的左節點設為目前節點，在紀錄分別的父節點。

LL:先將暫存的節點設為目前節點的左節點，再將目前節點的左節點設為暫存節點的右節點，再將暫存節點的右節點設為目前節點，在紀錄分別的父節點。

LR:先做RR再做LL。

RL:先做LL再做RR。





