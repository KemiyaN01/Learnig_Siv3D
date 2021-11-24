# include <Siv3D.hpp> // OpenSiv3D v0.6.3
#define STR(var) #var //マクロの引数を文字列リテラルに置換するマクロ関数


void TextureFileOpen();
void Option_Rename();

enum Option {ALBEDO,METALLIC,NORMAL,HEIGHT,OCLLUSION,EMISSION,DETAIL,ALBEDO_SECCOND,NORMAL_SECCOND};
const Array<std::string> Option_string = {"ALBEDO","METALLIC","NORMAL","HEIGHT","OCLLUSION","EMISSION","DETAIL","ALBEDO_SECCOND","NORMAL_SECCOND"};

Optional<FilePath> Textures_Folder;

TextEditState Option_text;

bool Option_Done = false;

void Main()
{
    const Font font{15};
    
    const Font Done{40};
    
    bool Option_check = false;
    
    
    
    while (System::Update())
    {
        
        
        if (SimpleGUI::Button(U"FileOpen", Vec2{ 20,20 }))
        {
            Textures_Folder = Dialog::SelectFolder();
        }
        if(Textures_Folder){
            
            SimpleGUI::CheckBox(Option_check, U"オプション", Vec2{20,130});
            if (Option_check == true) {
                font(U"オプションで生成するディレクトリの名前を変える。").draw(20,170);
                font(U"/を入れるとディレクトリが深くなる可能性があります。").draw(20,200);
                SimpleGUI::TextBox(Option_text, Vec2{20,230});
                if (Option_text.text.narrow().empty()) {
                    font(U"何も入力がない場合、ファイルが入っているディレクトリ名で整理されます。").draw(20,270);
                    if(SimpleGUI::Button(U"Excute", Vec2{20,60})){
                        TextureFileOpen();
                    }
                }else{
                    if(SimpleGUI::Button(U"Excute", Vec2{20,60})){
                        Option_Rename();
                    }
                }
            }else{
                if(SimpleGUI::Button(U"Excute", Vec2{20,60})){
                    TextureFileOpen();
                }
            }
        }
        
        if (Option_Done == true) {
            Done(U"Done!").draw(20,300);
            Done(U"終わりました!").draw(20,350);
            Done(U"escキーでもウィンドウを消せます!").draw(20,400);
        }
    }
}
void TextureFileOpen(){
    
    for (const auto& i : FileSystem::DirectoryContents(*Textures_Folder)) {
        std::string check = i.narrow();
        transform(check.begin(), check.end(), check.begin(), toupper);
        for (int Option_size = 0; Option_size < (int)Option_string.size(); Option_size++) {
            
            if(check.find(Option_string[Option_size]) != std::string::npos){
                if (FileSystem::IsFile(i)){
                    
                    FileSystem::CreateDirectories(*Textures_Folder+U"/"+FileSystem::BaseName(*Textures_Folder)+U"_"+Unicode::Widen(Option_string[Option_size]));
                    FileSystem::Rename(i, *Textures_Folder+U"/"+FileSystem::BaseName(*Textures_Folder)+U"_"+Unicode::Widen(Option_string[Option_size])+U"/"+FileSystem::FileName(i));
                }
                break;
            }
        }
    }
    Option_Done = true;
}
void Option_Rename(){
    
    for (const auto& i : FileSystem::DirectoryContents(*Textures_Folder)) {
        std::string check = i.narrow();
        transform(check.begin(), check.end(), check.begin(), toupper);
        for (int Option_size = 0; Option_size < (int)Option_string.size(); Option_size++) {
            
            if(check.find(Option_string[Option_size]) != std::string::npos){
                if (FileSystem::IsFile(i)){
                    
                    FileSystem::CreateDirectories(*Textures_Folder+U"/"+Option_text.text+U"_"+Unicode::Widen(Option_string[Option_size]));
                    FileSystem::Rename(i, *Textures_Folder+U"/"+Option_text.text+U"_"+Unicode::Widen(Option_string[Option_size])+U"/"+FileSystem::FileName(i));
                }
                break;
            }
        }
    }
    Option_Done = true;
}

// = アドバイス =
// アプリケーションをビルドして実行するたびにファイルアクセス許可のダイアログが表示されるのを避けたい場合、
// プロジェクトのフォルダを ユーザ/(ユーザ名)/アプリケーション/ などに移動させると良いです。
// Web カメラ、マイク使用時の許可ダイアログは消せません。
//
// = お役立ちリンク | Quick Links =
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加
// Slack や Twitter, BBS で気軽に質問や情報交換ができます。
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
