/**    
 * CODETANK 
 * Copyright (c) 2012, Tencent AlloyTeam, All rights reserved.
 * http://CodeTank.AlloyTeam.com/
 *
 * @version     1.0
 * @author      AlloyTeam
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
    
    //����Ѳ��
    var patrol = {
        aroundMap: function(t) {
            t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 0), function(){
				t.setAhead(t.getBattleFieldWidth() - t.getX() - t.DiagonalLength / 2.0, function() {
					t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 90), function(){
						t.setAhead(t.getY() - t.DiagonalLength / 2.0, function() {
							t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 180), function() {
								t.setAhead(t.getX() - t.DiagonalLength / 2.0, function() {
									t.setTurn(-1.0 * t.getMinAngle(t.getHeading(), 270), function() {
										t.setAhead(t.getBattleFieldHeight() - t.getY() - t.DiagonalLength / 2.0, function() {
											patrol.aroundMap(t);
										});
									});
								});
							});
						});
					});
				});
			});
        }
    };
	
	var radar = {
		sts : true,
		search : function(t) {
			if(radar.sts) {
				t.turnGunLeft(10, function(){
					radar.search(t);
				});
			} else {
				patrol.aroundMap(t);
			}
		}
	};
    
    Robot = new J.Class({extend : tank.Robot},{
		/**
		*robot��ѭ��
		**/	
        
        DELTA: 0.01,
		
		getMinAngle: function(angleA, angleB){
            var angleToTurn = angleB - angleA;        
            while(angleToTurn > 180) {
                angleToTurn -= 360;
            }
            while(angleToTurn < -180) {
                angleToTurn += 360;
            }
			return angleToTurn;
        },
		
		
        
		run:function(){
            this.DiagonalLength = Math.sqrt(this.getWidth() * this.getWidth() + this.getHeight() * this.getHeight());
			this.setAdjustGunForRobotTurn(true);
    		this.setAdjustRadarForGunTurn(false);
			//radar.search(this);
			this.loop(function(){
					this.turnGunLeft(10);
			});
		},

		/**
		*��������robot�Ĵ������
		**/
		onScannedRobot:function(e){
    		this.say("���Ǹ�");
			this.setGunTurn(-1.0 * this.getMinAngle(this.getGunHeading(), this.getHeading() + e.getBearing()));
			this.fire(3);
			this.scan();
            if(radar.sts) {
        	    patrol.aroundMap(this);   
			}
			radar.sts = false;
		},

		/**
		*���ӵ����еĴ������
		**/
		onHitByBullet:function(e){
			this.say("˭���ң��Ҵ�˭");
		},

		/**
		*��ǽ��ײ�Ĵ������
		**/
		onHitWall:function(e){
			this.say("�ⲻ����");
		},

		onRobotDeath:function(e){
			this.say("�����ˣ�����ëҲ��������������");
		}
	});
});