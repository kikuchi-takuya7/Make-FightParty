=====================================================================================
作品名　　:　Make&FightParty
ジャンル　:　アクションゲーム
制作者　　:　東北電子専門学校 ゲームエンジニア科 2年　菊地 巧椰
制作人数　:  1人
制作期間　:  4か月
=====================================================================================

1.動画URL

	https://youtu.be/U2Y4nqeK52M

2.概要

	・DirextXのエンジンを使用してアルティメットチキンホースとStick Fight: The Gameを参考にして作った3Dアクションゲームです。
 	・試合をする度にクリエイトモードに入り、設置するオブジェクトを選んで、それをステージに設置をしてまた試合を繰り返すゲームです。
	・勝利やキルでもらえるポイントが一定まで一番早く溜まったプレイヤーが優勝です。
	・左上のテキストでメタAIのやっている事とキャラAIが誰を狙うパターンを使っているのかが分かります。（No1なら一位の誰かを狙う、Counterなら殴ってきた相手を狙う等）

3.開発環境

　　　・ハードウェア	：WindowsPC(i7-12700H、メモリ32GB)
　　　・開発用ＯＳ	：Windows11
　　　・統合開発環境	：Microsoft Visual Studio 2022
　　　・開発言語      	： C / C++ / HLSL
　　　・ライブラリ      	： directX11 / FBXSDK

4.操作説明

　　　・入力デバイス ： マウス、キーボード

試合中での操作

　　　・WASD	：移動
　　　・スペースキー	：攻撃、結果等のゲージを飛ばしたり、要所要所で次に進むために使います


クリエイトモードでの操作
　　　・マウスカーソル：設置したいオブジェクトを選択、設置したい場所に合わせて設置
　　　・左クリック	：オブジェクトを選択、設置
　　　・矢印キー	：オブジェクトの向きを変える

5.作品に対するアピールポイント
　　　
　　　・ゲームAI(メタAI,キャラAI,ナビAI)を使用してCPUが自立して移動、攻撃、オブジェクトの設置を行うようにしました。
　　　・キャラクターAIはCPUの操作、メタAIは試合全体の動きや順位等の管理、ナビAIは様々な情報を保持する等、AI毎の役割がはっきりするように意識しました。
　　　・Astarアルゴリズムを使い、CPUが壁等を認識してなるべく避けるようにプログラムしました。
　　　・クリエイトモードで最下位の人から順にオブジェクトを選べるようにし、CPUも一位から優先して狙うようにしたので、最下位の人が勝ちやすくなるように工夫しました。　　　
　　　・CPUとプレイヤーのどちらにも共通するstateパターンを使う事で、拡張性を上げました。
　　　・enumの数分の大きさの配列を作り、swich文を使わなくてもstateの切り替えができるように工夫しました。
　　　・ステージを1×1のブロックで構成する事で、マウスからレイを飛ばしてレイが当たったステージのその位置にオブジェクトを置けるように工夫しました。
　　　・途中経過等のUIがパッとわかるように工夫しました。
　　　・アニメーションがなるべく自然な動きになるようにmayaで丁寧に作りました。
　　　・無名名前空間等を使い、なるべくマジックナンバーを使わないように工夫しました。


6.反省点、改善点
　　　・11月～12月中旬にIKを実装しようと色々試していたが、結局実装できずに時間を浪費してしまった。
	→事前にその実装にかける期限を決めて、その期限内に無理そうならすぐに諦めるべきだった。

　　　・プランナーが値をいじる事が難しくなってしまった。
	→ImGuiライブラリとjsonファイルを使い、値をいじれる様にするべきだった。
　　　
7.今後の目標
　　　・カメラをスマブラみたいに動くようにする
　　　・選択できるオブジェクトの数を増やし、状況によって出現率を変更する
　　　・AIの種類をCSVで変更できるようにする


使わせていただいた効果音・BGMサイト様

タイトルBGM：sunrise	URL:https://dova-s.jp/bgm/play1561.html
戦闘中のBGM：ウルトラ大掃除	URL:https://dova-s.jp/bgm/play8657.html
クリエイトモードのBGM：夢物語	URL:https://soundcloud.com/baron1_3/yumemonogatari
優勝時のBGM：ニコニコモンズ	URL:https://commons.nicovideo.jp/works/nc100688

効果音：効果音ラボ	URL:https://soundeffect-lab.info/sound/battle/
