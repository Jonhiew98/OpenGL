precision mediump float;
varying vec4 fColor; 
varying vec2 fTexCoord;

uniform sampler2D sampler2d;
uniform float Factor1;
uniform float SpectrumLeft;
uniform float SpectrumRight;

void main()                           
{     
//===================================================================================		
	// rainbow
	float x = gl_FragCoord.x * 0.01;
	float huehue = sin(Factor1) * 5.0;
	float r = sin(x*2.0 + huehue) *0.5 + 0.5;	
	float g = sin(x*2.0 + 2.0+ huehue) *0.5 + 0.5;	
	float b = sin(x*2.0 + 4.0+ huehue)* 0.5 + 0.5;
	
	vec4 rainbowColor = vec4(r,g,b,1.0);
	//gl_fragcolor = vec4 (r, g, b, 1.0);
//======================================================================================				
	vec4 texColor = texture2D(sampler2d, fTexCoord);
	vec4 combinedColor; 
	combinedColor =fColor * texColor;
	
	vec4 resultColor;
	resultColor.r = mod(combinedColor.r + cos(Factor1 * 2.0),1.0);
	resultColor.g = mod(combinedColor.g + cos(Factor1 * 2.0),1.0);
	resultColor.b = mod(combinedColor.b + cos(Factor1 * 5.0),1.0);
	resultColor.a = combinedColor.a;
	
	gl_FragColor = resultColor;
	
	//use texture color only
	gl_FragColor = texture2D(sampler2d,fTexCoord);
//=======================================================================================	
	//grayScale
	/*vec4 texColor = texture2D(sampler2d, fTexCoord);
	float average = (texColor.r + texColor.g + texColor.b) /3.0;
	vec4 finalColor = vec4(average,average,average,1.0);
	
	gl_FragColor = finalColor;
	*/	
//=============================================================================================			
	//ring
	float expandSpeed = Factor1 * 10.0;
	float yCenter = 300.0;
	float xCenter = 400.0;
	
	float radius = 185.0 + ((sin(0.3*expandSpeed)*100.0)) + (SpectrumRight*20.0);
	float radius2 = 170.0 + ((sin(0.3*expandSpeed)*100.0)) + (SpectrumRight*20.0);
		
	float distance;
	float distance2;
	
	float mixtureGreen;
	float mixtureRed;
	float mixtureGreen2;
	
	mixtureGreen = sin(x*2.0 + 2.0+ huehue) *0.5 + 0.5;
	mixtureGreen2 = cos(x*2.0 + 2.0+ huehue) *0.5 + 0.5;
	mixtureRed = sin(x*2.0 + huehue) *0.5 + 0.5;
			
	distance = sqrt(pow(gl_FragCoord.x - xCenter,2.0) + pow(gl_FragCoord.y - yCenter,2.0));
	distance2 = sqrt(pow(gl_FragCoord.x - xCenter,2.0) + pow(gl_FragCoord.y - yCenter,2.0));
	if(distance < radius)
	{
		gl_FragColor = vec4 ( mixtureRed, mixtureGreen, 1.0,1.0);
	}
		
	if(distance2 < radius2)
	{
		gl_FragColor = texColor;
	}
		
//================================================================================================		
	//ring2	
	float radius4 = 85.0 + ((cos(0.3*expandSpeed * 1.5)*100.0));
	float radius5 = 70.0 + ((cos(0.3*expandSpeed * 1.5)*100.0));
		
	float distance4;
	float distance5;
		
	distance4 = sqrt(pow(gl_FragCoord.x - xCenter,2.0) + pow(gl_FragCoord.y - yCenter,2.0));
	distance5 = sqrt(pow(gl_FragCoord.x - xCenter,2.0) + pow(gl_FragCoord.y - yCenter,2.0));
	if(distance4 < radius4)
	{
		gl_FragColor = vec4 ( mixtureRed, mixtureGreen2, 1.0,1.0);
	}
		
	if(distance5 < radius5)
	{
		gl_FragColor = texColor;
	}
		
//==============================================================================================			
	//middle circle
	float radius3 = 100.0+ (SpectrumLeft*10.0);
	float distance3;
	vec4 middleColor;
	middleColor.r = mod(combinedColor.r + tan(Factor1 * 2.0),1.0);
	middleColor.g = mod(combinedColor.g + sin(Factor1 * 2.0),1.0);
	middleColor.b = mod(combinedColor.b + cos(Factor1 * 5.0),1.0);
	middleColor.a = combinedColor.a;
	
	distance3 = sqrt(pow(gl_FragCoord.x - xCenter,2.0) + pow(gl_FragCoord.y - yCenter,2.0));
	
	if(distance3 < radius3)
	{
		gl_FragColor = vec4 ( mixtureRed, mixtureGreen, 1.0,1.0);	
	}
	
//===============================================================================================	
	
	// middle animation
	for(float i = 0.0; i < 100.0; i++)
	{
		float speed = Factor1 * 5.0;
		float theta = i * 360.0;
		float radius4 = 60.0;
		float circleGap = 150.0;
				
		float xPos2 = (radius4 + abs( circleGap* cos(theta + speed))) * cos(theta) + xCenter;
		float yPos2 = (radius4 + abs( circleGap* sin(theta + speed))) * sin(theta) + yCenter;
		
		float cDistance = sqrt(pow(gl_FragCoord.x - xPos2,2.0) + pow(gl_FragCoord.y - yPos2,2.0));
		float changeRad = 5.0;
		
		if(cDistance < changeRad)
		{
			gl_FragColor = vec4 ( mixtureRed, mixtureGreen, 1.0,1.0);
		}
	}
	
		
		
		
	
















	
} 