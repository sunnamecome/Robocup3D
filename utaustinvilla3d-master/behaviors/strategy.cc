#include "naobehavior.h"
#include "../rvdraw/rvdraw.h"

extern int agentBodyType;

/*
 * Real game beaming.
 * Filling params x y angle
 */
void NaoBehavior::beam( double& beamX, double& beamY, double& beamAngle ) {
    beamX = -HALF_FIELD_X + worldModel->getUNum();
    beamY = 0;
    beamAngle = 0;
}


SkillType NaoBehavior::selectSkill() {
    //题目出现bug，无论怎样无法踢向球门，我的解决方法是把接应点固定
    VecPosition Posball=worldModel->getBall();
    VecPosition Target[6]={
        Posball+VecPosition(-0.5,0),//控球位
        VecPosition(-15,0+worldModel->getBall().getY()/10),//守门位
        VecPosition(9,4),//接应位1
        VecPosition(9,-4),//接应位2
        VecPosition((Posball.getX()-15)/2,Posball.getY()/2+5) ,//防守点1
        VecPosition((Posball.getX()-15)/2,Posball.getY()/2-5)//防守点2
        
    };

vector<vector<double>>dis(6, vector<double>(6,0));
int BotForTarget[6]={0};
VecPosition Pos = VecPosition(0,0,0);

for(int i=0;i<6;i++){
    for(int j=0;j<6;j++){
        int playerNum = WO_TEAMMATE1 + j;
        WorldObject *tem = worldModel->getWorldObject(playerNum);
        if (worldModel->getUNum() == playerNum){
            Pos = me;//若是遍历到"我",则获取"我"的位置
            if(worldModel->isFallen())
            {
                dis[i][j]++;//摔倒花费加1；               
            }
        }
        else{
            tem = worldModel->getWorldObject(WO_TEAMMATE1 + j );
            Pos = tem->pos;//若是队友则获取队友的位置
        }
        dis[i][j]=Target[i].getDistanceTo(Pos);//dis[i][j]保存第i个target到第j名球员的位置
    }
}


for(int i=0;i<6;i++){
    int robot = min_element(dis[i].begin(), dis[i].begin() + 6) -dis[i].begin();//找到距离最⼩的球员
    BotForTarget[i]=robot;//保存该球员编号
    for(int j=0;j<6;j++)
        dis[j][robot]=10000;//不再考虑该球员，就将他的距离全设成最⼤
}

// for(int i=0;i<6;i++){
//     if (WO_OPPONENT1+BotForTarget[i]==i){
//         BotForTarget[0] = VecPosition target[0];
//     }
//     else{

//     }
// }


for(int i=0;i<6;i++)
{
    if (worldModel->getUNum() == WO_TEAMMATE1+BotForTarget[i])//若我的编号和分配球员数组中编号相同
    {
        if(worldModel->getUNum() == WO_TEAMMATE1+BotForTarget[0] && me.getDistanceTo(ball) <3&& me.getX()<=-15+PENALTY_X&&abs(me.getY())<=PENALTY_Y) 
        //我控球且我在球附近且我在禁区内
        {
            VecPosition tar = VecPosition(0,0);

            for(int i = 1 ; i< 6;i++)
            {
                double minq = 100000;
                if(me.getDistanceTo(WO_TEAMMATE1+BotForTarget[i])<minq)
                {
                    minq = me.getDistanceTo(WO_TEAMMATE1+BotForTarget[i]);
                    WorldObject *sss = worldModel->getWorldObject(WO_TEAMMATE1+BotForTarget[i]);
                    tar = sss->pos;//若是队友则获取队友的位置
                    
                }
            }
            cout << "111s"<<endl;
            return kickBall(10,tar); //禁区内踢给防守

        }
         if((worldModel->getUNum() == WO_TEAMMATE1+BotForTarget[0] && me.getDistanceTo(ball) <3)&&( me.getX()>=-15+PENALTY_X||abs(me.getY())>=PENALTY_Y)) 
        //我控球且我在球附近且我在禁区外
        {
            cout << "111"<<endl;

           if(Posball.getX() <= Target[2].getX()||Posball.getX() <= Target[3].getX()) // buhshi接应点
           {
            return kickBall(10,Target[2]);
           }          
            else
            {
                return kickBall(10,VecPosition(15,0));//是接应点

            }

        }
        cout << "sss"<<endl;

        return goToTarget(collisionAvoidance(true, false, false, 1,.5,Target[i], true));//就跑向对应的点位
    }
    //题目出现bug，无论怎样无法踢向球门，我的解决方法是把接应点固定
}
//题目出现bug，无论怎样无法踢向球门，我的解决方法是把接应点固定


    // My position and angle
    //cout << worldModel->getUNum() << ": " << worldModel->getMyPosition() << ",\t" << worldModel->getMyAngDeg() << "\n";

    // Position of the ball
    //cout << worldModel->getBall() << "\n";

    // Example usage of the roboviz drawing system and RVSender in rvdraw.cc.
    // Agents draw the position of where they think the ball is
    // Also see example in naobahevior.cc for drawing agent position and
    // orientation.
    /*
    worldModel->getRVSender()->clear(); // erases drawings from previous cycle
    worldModel->getRVSender()->drawPoint("ball", ball.getX(), ball.getY(), 10.0f, RVSender::MAGENTA);
    */

    // ### Demo Behaviors ###

    // Walk in different directions
    //return goToTargetRelative(VecPosition(1,0,0), 0); // Forward
    //return goToTargetRelative(VecPosition(-1,0,0), 0); // Backward
    //return goToTargetRelative(VecPosition(0,1,0), 0); // Left
    //return goToTargetRelative(VecPosition(0,-1,0), 0); // Right
    //return goToTargetRelative(VecPosition(1,1,0), 0); // Diagonal
    //return goToTargetRelative(VecPosition(0,1,0), 90); // Turn counter-clockwise
    //return goToTargetRelative(VecPdosition(0,-1,0), -90); // Turn clockwise
    //return goToTargetRelative(VecPosition(1,0,0), 15); // Circle

    // Walk to the ball
    //return goToTarget(ball);

    // Turn in place to face ball
    /*double distance, angle;
    getTargetDistanceAndAngle(ball, distance, angle);
    if (abs(angle) > 10) {
      return goToTargetRelative(VecPosition(), angle);
    } else {
      return SKILL_STAND;
    }*/

    // Walk to ball while always facing forward
    //return goToTargetRelative(worldModel->g2l(ball), -worldModel->getMyAngDeg());

    // Dribble ball toward opponent's goal
    //return kickBall(KICK_DRIBBLE, VecPosition(HALF_FIELD_X, 0, 0));

    // Kick ball toward opponent's goal
    //return kickBall(KICK_FORWARD, VecPosition(HALF_FIELD_X, 0, 0)); // Basic kick
    //return kickBall(KICK_IK, VecPosition(HALF_FIELD_X, 0, 0)); // IK kick

    // Just stand in place
    //return SKILL_STAND;

    // Demo behavior where players form a rotating circle and kick the ball
    // back and forth

}


/*
 * Demo behavior where players form a rotating circle and kick the ball
 * back and forth
 */
SkillType NaoBehavior::demoKickingCircle() {
    // Parameters for circle
    VecPosition center = VecPosition(-HALF_FIELD_X/2.0, 0, 0);
    double circleRadius = 5.0;
    double rotateRate = 2.5;

    // Find closest player to ball
    int playerClosestToBall = -1;
    double closestDistanceToBall = 10000;
    for(int i = WO_TEAMMATE1; i < WO_TEAMMATE1+NUM_AGENTS; ++i) {
        VecPosition temp;
        int playerNum = i - WO_TEAMMATE1 + 1;
        if (worldModel->getUNum() == playerNum) {
            // This is us
            temp = worldModel->getMyPosition();
        } else {
            WorldObject* teammate = worldModel->getWorldObject( i );
            if (teammate->validPosition) {
                temp = teammate->pos;
            } else {
                continue;
            }
        }
        temp.setZ(0);

        double distanceToBall = temp.getDistanceTo(ball);
        if (distanceToBall < closestDistanceToBall) {
            playerClosestToBall = playerNum;
            closestDistanceToBall = distanceToBall;
        }
    }

    if (playerClosestToBall == worldModel->getUNum()) {
        // Have closest player kick the ball toward the center
        return kickBall(KICK_FORWARD, center);
    } else {
        // Move to circle position around center and face the center
        VecPosition localCenter = worldModel->g2l(center);
        SIM::AngDeg localCenterAngle = atan2Deg(localCenter.getY(), localCenter.getX());

        // Our desired target position on the circle
        // Compute target based on uniform number, rotate rate, and time
        VecPosition target = center + VecPosition(circleRadius,0,0).rotateAboutZ(360.0/(NUM_AGENTS-1)*(worldModel->getUNum()-(worldModel->getUNum() > playerClosestToBall ? 1 : 0)) + worldModel->getTime()*rotateRate);

        // Adjust target to not be too close to teammates or the ball
        target = collisionAvoidance(true /*teammate*/, false/*opponent*/, true/*ball*/, 1/*proximity thresh*/, .5/*collision thresh*/, target, true/*keepDistance*/);

        if (me.getDistanceTo(target) < .25 && abs(localCenterAngle) <= 10) {
            // Close enough to desired position and orientation so just stand
            return SKILL_STAND;
        } else if (me.getDistanceTo(target) < .5) {
            // Close to desired position so start turning to face center
            return goToTargetRelative(worldModel->g2l(target), localCenterAngle);
        } else {
            // Move toward target location
            return goToTarget(target);
        }
    }
}


