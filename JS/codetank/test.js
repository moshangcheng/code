/**    
 * CODETANK 
 * Copyright (c) 2012, Tencent AlloyTeam, All rights reserved.
 * http://CodeTank.AlloyTeam.com/
 *
 * @version     1.0
 * @author      moshangcheng
 *
 *  .d8888b.                888      88888888888               888   TM   
 * d88P  Y88b               888      ''''888''''               888      
 * 888    888               888          888                   888      
 * 888         .d88b.   .d88888  .d88b.  888  8888b.  88888b.  888  888 
 * 888        d88""88b d88" 888 d8P  Y8b 888     "88b 888 "88b 888 .88P 
 * 888    888 888  888 888  888 88888888 888 .d888888 888  888 888888K  
 * Y88b  d88P Y88..88P Y88b 888 Y8b.     888 888  888 888  888 888 "88b 
 *  "Y8888P"   "Y88P"   "Y88888  "Y8888  888 "Y888888 888  888 888  888 
 * 
 */

Jx().$package(function(J){   
    
    Robot = new J.Class({extend : tank.Robot},{
    	/**
		*robot主循环
		**/
       run:function(){
            this.DiagonalLength = Math.sqrt(this.getWidth() * this.getWidth() + this.getHeight() * this.getHeight());
			this.setAdjustGunForRobotTurn(true);
    		this.setAdjustRadarForGunTurn(false);
			//this.loop(function(){
				this.setAhead(500);
				this.setTurn(60, function(){
					this.say(console.log("bb" + new Date()));
				});
				this.execute();
                this.say(console.log("aa" + new Date()));
			//});
		},

		/**
		*看到其他robot的处理程序
		**/
		onScannedRobot:function(e){
    		this.say("就是干");
		},

		/**
		*被子弹击中的处理程序
		**/
		onHitByBullet:function(e){
			this.say("谁打我，我打谁");
		},

		/**
		*和墙碰撞的处理程序
		**/
		onHitWall:function(e){
			this.say("这不可能");
		},

		onRobotDeath:function(e){
			this.say("我死了，连羽毛也腐烂在土地里面");
		}
	});
});