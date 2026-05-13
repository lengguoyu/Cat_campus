#include "StoryManager.h"
#include "AttributeManager.h"
#include "GameManager.h"
#include <QRandomGenerator>

StoryManager& StoryManager::getInstance()
{
    static StoryManager instance;
    return instance;
}

void StoryManager::addNode(const StoryNode& node)
{
    m_nodes[node.id] = node;
}

void StoryManager::setFlag(const QString& flag, bool value)
{
    m_flags[flag] = value;
}

bool StoryManager::getFlag(const QString& flag) const
{
    return m_flags.value(flag, false);
}

StoryNode StoryManager::getNode(int id) const
{
    return m_nodes.value(id);
}

void StoryManager::buildStoryTree()
{
    m_nodes.clear();

    // 节点0：第一幕
    StoryNode act1;
    act1.id = 0;
    act1.sceneId = "bedroom";
    act1.text = "朝阳温柔地透过窗户，63在晨曦微光中醒来，崭新的上学日正式开启。\n\n门外传来猫妈妈小夏的声音：\"63，快起床啦！上学要迟到了！早餐我给你做好了，我先去上班咯！\"";
    act1.imagePath = ":/images/bedroom.jpg";
    act1.options = {
        {"再睡五分钟", [this]() {
             AttributeManager::getInstance().addSleep(20);
             m_firstActChoice = 1;
             setCurrentNodeId(2);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"马上就起", [this]() {
             AttributeManager::getInstance().addWisdom(10);
             m_firstActChoice = 2;
             setCurrentNodeId(2);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act1);

    // 节点2：第二幕
    StoryNode act2;
    act2.id = 2;
    act2.sceneId = "living_room";
    act2.text = "来到客厅，温暖的晨光洒在窗边的风信子上，紫色的花朵轻轻摇曳。\n\n桌子上摆着猫妈妈小夏做的早餐：一碗热腾腾的清汤面，撒着翠绿葱花，暖心又暖胃。";
    act2.imagePath = ":/images/living_room.jpg";
    act2.options = {
        {"吃完妈妈做的爱心面条再出发", [this]() {
             if (m_firstActChoice == 1) {
                 AttributeManager::getInstance().addWarmth(10);
             } else {
                 AttributeManager::getInstance().addWarmth(12);
             }
             m_secondActChoice = 1;
             setCurrentNodeId(3);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"出门买烧麦，带去教室食用", [this]() {
             m_secondActChoice = 2;
             int rand = QRandomGenerator::global()->bounded(100);
             m_isDiarrhea = (rand < 50);
             setCurrentNodeId(3);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act2);

    // 节点3：第三幕
    StoryNode act3;
    act3.id = 3;
    act3.sceneId = "classroom";
    act3.imagePath = ":/images/classroom.jpg";

    if (m_firstActChoice == 1) {
        act3.text = "63一路狂奔，最终还是迟到了。\n\n刚推开教室门，班主任小猫福禄抬了抬眼镜：\"63，快点回去坐好，天天瞌睡这么多。\"\n\n63腼腆一笑，快步走到座位。";
        AttributeManager::getInstance().addWisdom(-10);
    } else if (m_firstActChoice == 2) {
        int rand = QRandomGenerator::global()->bounded(100);
        if (rand < 60) {
            act3.text = "63提前到达教室，安安稳稳坐下，还能好好背一会儿单词。同桌小猫17推了推眼镜：\"63，你今天来的好早哦。\"63挠挠头不好意思地笑了笑。";
            AttributeManager::getInstance().addWisdom(10);
        } else {
            act3.text = "同桌小猫17拿出63最爱吃的小饼干：\"63，你今天来的好早哦。我给你带了你最爱吃的小饼干。\"\n\n63两眼放光，开心得几乎跳起来！低头偷笑：\"谢谢你！我爱你！\"";
            AttributeManager::getInstance().addWarmth(15);
        }
    } else {
        act3.text = "63顺利到达教室，开始了新的一天。";
    }

    act3.options = {
        {"继续", [this]() {
             setCurrentNodeId(4);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act3);

    // 节点4：第四幕
    StoryNode act4;
    act4.id = 4;
    act4.sceneId = "classroom";
    act4.text = "上课铃响，语文课开始。\n\n语文老师笑着说：\"今天做高考语文古诗词抽背训练，每个同学都要准备好，随时有可能抽到你！\"";
    act4.imagePath = ":/images/classroom.jpg";
    act4.options = {
        {"开始答题挑战", [this]() {
             GameManager::getInstance().triggerPoetryGame();
         }}
    };
    addNode(act4);

    // 节点5：第五幕
    StoryNode act5;
    act5.id = 5;
    act5.sceneId = "canteen";
    act5.text = "上午的课程结束，午餐时间到。\n\n小猫17凑过来：\"63，今天吃什么？我纠结好久了。\"";
    act5.imagePath = ":/images/canteen.jpg";
    act5.options = {
        {"来一碗热气腾腾的羊肉粉", [this]() {
             AttributeManager::getInstance().addWarmth(5);
             AttributeManager::getInstance().addSleep(10);
             setCurrentNodeId(6);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"选一份鲜香可口的小炒", [this]() {
             AttributeManager::getInstance().addWarmth(10);
             AttributeManager::getInstance().addSleep(-10);
             setCurrentNodeId(6);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act5);

    // 节点6：过渡
    StoryNode act5b;
    act5b.id = 6;
    act5b.sceneId = "classroom";
    act5b.text = "午餐结束，下午的课程还没开始...";
    act5b.imagePath = ":/images/classroom.jpg";
    act5b.options = {
        {"继续", [this]() {
             setCurrentNodeId(7);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act5b);

    // 节点7：第六幕
    StoryNode act6;
    act6.id = 7;
    act6.sceneId = "free_time";
    act6.text = "好不容易的空闲时间，到底做点什么好呢？";
    act6.imagePath = ":/images/free_time.jpg";
    act6.options = {
        {"好好午睡一下吧", [this]() {
             AttributeManager::getInstance().addSleep(20);
             m_flags["took_nap"] = true;
             setCurrentNodeId(8);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"不然去逛一下吧", [this]() {
             m_flags["took_nap"] = false;
             setCurrentNodeId(9);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act6);

    // 节点8：午睡后
    StoryNode act6a;
    act6a.id = 8;
    act6a.sceneId = "classroom";
    act6a.text = "这一觉睡得格外安稳，还做了个甜甜的好梦，醒来时整个人都轻松舒服。\n\n上课铃响了，下午第一节课是数学课。";
    act6a.imagePath = ":/images/classroom.jpg";
    act6a.options = {
        {"准备上课", [this]() {
             setCurrentNodeId(10);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act6a);

    // 节点9：地图
    StoryNode act6b;
    act6b.id = 9;
    act6b.sceneId = "free_time";
    act6b.text = "思虑了半天，63决定去逛逛校园。\n\n该去哪里好呢？";
    act6b.imagePath = ":/images/free_time.jpg";
    act6b.options = {
        {"去图书馆看看", [this]() {
             setCurrentNodeId(11);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"去钢琴房听听音乐", [this]() {
             setCurrentNodeId(12);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(act6b);

    // 节点11：图书馆
    StoryNode library;
    library.id = 11;
    library.sceneId = "library";
    library.text = "63来到图书馆，拿了一本《猫类简史》看了起来。这时候，书架处好像有摩擦声。";
    library.imagePath = ":/images/library.jpg";
    library.options = {
        {"过去看看", [this]() {
             AttributeManager::getInstance().addWarmth(50);
             AttributeManager::getInstance().addWisdom(5);
             setCurrentNodeId(13);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"继续看书", [this]() {
             AttributeManager::getInstance().addWisdom(15);
             setCurrentNodeId(13);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(library);

    // 节点12：钢琴房
    StoryNode piano;
    piano.id = 12;
    piano.sceneId = "piano_room";
    piano.text = "63来到钢琴房，优美的琴音从指间流出。学长正在专注地弹奏。";
    piano.imagePath = ":/images/piano_room.jpg";
    piano.options = {
        {"上前提醒", [this]() {
             AttributeManager::getInstance().addWarmth(15);
             AttributeManager::getInstance().addWisdom(5);
             setCurrentNodeId(13);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"默默关门", [this]() {
             AttributeManager::getInstance().addWarmth(80);
             m_flags["closed_piano_door"] = true;
             setCurrentNodeId(13);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(piano);

    // 节点10：数学课
    StoryNode mathEntry;
    mathEntry.id = 10;
    mathEntry.sceneId = "classroom";
    mathEntry.imagePath = ":/images/classroom.jpg";

    if (m_flags.value("took_nap", false)) {
        mathEntry.text = "精力充沛，兴致勃勃上数学课。";
        AttributeManager::getInstance().addWisdom(10);
    } else {
        mathEntry.text = "数学课上昏昏欲睡，在梦里和周公讨论圆锥曲线。";
    }

    mathEntry.options = {
        {"继续", [this]() {
             setCurrentNodeId(14);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(mathEntry);

    // 节点13：数学课过渡
    StoryNode mathTrans;
    mathTrans.id = 13;
    mathTrans.sceneId = "classroom";
    mathTrans.text = "课间休息时间到了。";
    mathTrans.imagePath = ":/images/classroom.jpg";
    mathTrans.options = {
        {"继续", [this]() {
             setCurrentNodeId(14);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(mathTrans);

    // 节点14：八卦
    StoryNode gossip;
    gossip.id = 14;
    gossip.sceneId = "classroom";
    gossip.text = "数学课结束，课间闲来无事，小猫17悄悄凑过来。\n\n小猫17：\"你要听炸裂的还是不炸裂的？\"";
    gossip.imagePath = ":/images/classroom.jpg";
    gossip.options = {
        {"炸裂的", [this]() {
             AttributeManager::getInstance().addWarmth(10);
             AttributeManager::getInstance().addWisdom(-5);
             setCurrentNodeId(15);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"不炸裂的", [this]() {
             AttributeManager::getInstance().addWarmth(20);
             AttributeManager::getInstance().addWisdom(-5);
             setCurrentNodeId(15);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(gossip);

    // 节点15：晚霞
    StoryNode sunset;
    sunset.id = 15;
    sunset.sceneId = "sunset";
    sunset.text = "傍晚，天空忽然出现绝美晚霞，染红半边天空。\n\n小猫小颜指着窗外：\"我去，这么漂亮！\"";
    sunset.imagePath = ":/images/sunset.jpg";
    sunset.options = {
        {"写诗赞美", [this]() {
             AttributeManager::getInstance().addWisdom(10);
             m_flags["wrote_poem"] = true;
             setCurrentNodeId(16);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"专心干饭", [this]() {
             AttributeManager::getInstance().addWarmth(10);
             setCurrentNodeId(16);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"大喊赞叹", [this]() {
             AttributeManager::getInstance().addWisdom(-1);
             AttributeManager::getInstance().addWarmth(15);
             setCurrentNodeId(16);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(sunset);

    // 节点16：羽毛球
    StoryNode badmintonInvite;
    badmintonInvite.id = 16;
    badmintonInvite.sceneId = "classroom";
    badmintonInvite.text = "回到教室，还有40分钟上晚自习。小猫小Q跑来问：\"63！来打羽毛球吗？！\"";
    badmintonInvite.imagePath = ":/images/classroom.jpg";
    badmintonInvite.options = {
        {"接受邀请", [this]() {
             AttributeManager::getInstance().addWarmth(10);
             GameManager::getInstance().triggerBadmintonGame();
         }},
        {"拒绝邀请", [this]() {
             AttributeManager::getInstance().addWisdom(5);
             setCurrentNodeId(17);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(badmintonInvite);

    // 节点17：晚自习后
    StoryNode evening;
    evening.id = 17;
    evening.sceneId = "night_classroom";
    evening.text = "终于下了晚自习，脑袋都快学爆了，小猫小彤发来邀请：\"要一起走走吗？\"";
    evening.imagePath = ":/images/night_classroom.jpg";
    evening.options = {
        {"拒绝，肚子饿了", [this]() {
             setCurrentNodeId(18);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"接受邀请", [this]() {
             setCurrentNodeId(19);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(evening);

    // 节点18：夜市
    StoryNode nightMarket;
    nightMarket.id = 18;
    nightMarket.sceneId = "night_market";
    nightMarket.text = "校门口香气扑鼻，小猫小Q靠在墙边：\"63，一起吃点东西再回家？\"";
    nightMarket.imagePath = ":/images/night_market.jpg";
    nightMarket.options = {
        {"关东煮", [this]() {
             AttributeManager::getInstance().addWarmth(10);
             setCurrentNodeId(20);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"铁板豆腐", [this]() {
             AttributeManager::getInstance().addWarmth(8);
             setCurrentNodeId(20);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(nightMarket);

    // 节点19：救人剧情
    StoryNode rescue;
    rescue.id = 19;
    rescue.sceneId = "night_market";
    rescue.text = "路上遇到低年级小猫被黑车司机纠缠，情况紧急！";
    rescue.imagePath = ":/images/night_market.jpg";
    rescue.options = {
        {"上前帮忙", [this]() {
             AttributeManager::getInstance().addWarmth(60);
             AttributeManager::getInstance().addWisdom(10);
             setCurrentNodeId(20);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"原地观望", [this]() {
             AttributeManager::getInstance().addWarmth(-10);
             AttributeManager::getInstance().addWisdom(10);
             setCurrentNodeId(20);
             GameManager::getInstance().notifyStoryUpdate();
         }},
        {"报警", [this]() {
             AttributeManager::getInstance().addWisdom(20);
             AttributeManager::getInstance().addWarmth(70);
             m_flags["called_police"] = true;
             setCurrentNodeId(20);
             GameManager::getInstance().notifyStoryUpdate();
         }}
    };
    addNode(rescue);

    // 节点20：结束
    StoryNode end;
    end.id = 20;
    end.sceneId = "bedroom_night";
    end.text = "夜色降临，63结束了充实的一天。\n\n躺在床上，回想着今天的欢笑与小插曲，安心进入梦乡。";
    end.imagePath = ":/images/bedroom_night.jpg";
    end.options = {
        {"查看结局", [this]() {
             GameManager::getInstance().evaluateEnding();
         }}
    };
    addNode(end);
}