/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Ricardo Quesada
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
/*
"										\n\
#ifdef GL_ES							\n\
precision lowp float;					\n\
#endif									\n\
										\n\
varying vec4 v_fragmentColor;			\n\
										\n\
void main()								\n\
{										\n\
	gl_FragColor = v_fragmentColor;		\n\
}										\n\
";
 */

"    \n\
uniform float iGlobalTime;\n\
uniform vec3 iResolution;\n\
float noise(vec3 p) //Thx to Las^Mercury        \n\
{        \n\
vec3 i = floor(p);        \n\
vec4 a = dot(i, vec3(1., 57., 21.)) + vec4(0., 57., 21., 78.);        \n\
vec3 f = cos((p-i)*acos(-1.))*(-.5)+.5;        \n\
a = mix(sin(cos(a)*a),sin(cos(1.+a)*(1.+a)), f.x);        \n\
a.xy = mix(a.xz, a.yw, f.y);        \n\
return mix(a.x, a.y, f.z);        \n\
}        \n\
\n\
//-----------------------------------------------------------------------------        \n\
// Scene/Objects        \n\
//-----------------------------------------------------------------------------        \n\
float sphere(vec3 p, vec4 spr)        \n\
{        \n\
return length(spr.xyz-p) - spr.w;        \n\
}        \n\
\n\
float fire(vec3 p)        \n\
{        \n\
float d= sphere(p*vec3(1.,.5,1.), vec4(.0,-1.,.0,1.));        \n\
return d+(noise(p+vec3(.0,iGlobalTime*2.,.0))+noise(p*3.)*.5)*.25*(p.y) ;        \n\
}        \n\
//-----------------------------------------------------------------------------        \n\
// Raymarching tools        \n\
//-----------------------------------------------------------------------------        \n\
float scene(vec3 p)        \n\
{        \n\
return min(100.-length(p) , abs(fire(p)) );        \n\
}        \n\
\n\
\n\
\n\
vec4 Raymarche(vec3 org, vec3 dir)        \n\
{        \n\
float d=0.0;        \n\
vec3  p=org;        \n\
float glow = 0.0;        \n\
float eps = 0.02;        \n\
bool glowed=false;        \n\
for(int i=0; i<64; i++)        \n\
{        \n\
d = scene(p) + eps;        \n\
p += d * dir;        \n\
if( d>eps )        \n\
{        \n\
if( fire(p) < .0)        \n\
glowed=true;        \n\
if(glowed)        \n\
glow = float(i)/64.;        \n\
}        \n\
}        \n\
return vec4(p,glow);        \n\
}        \n\
\n\
//-----------------------------------------------------------------------------        \n\
// Main functions        \n\
//-----------------------------------------------------------------------------        \n\
\n\
void main()        \n\
{        \n\
//vec3 iResolution = vec3(800.0, 600.0, 1.0);\n\
vec2 v = -1.0 + 2.0 * gl_FragCoord.xy / iResolution.xy;        \n\
v.x *= iResolution.x/iResolution.y;        \n\
vec3 org = vec3(0.,-2.,4.);        \n\
vec3 dir   = normalize(vec3(v.x*1.6,-v.y,-1.5));        \n\
vec4 p = Raymarche(org,dir);        \n\
float glow = p.w;        \n\
gl_FragColor = mix(vec4(0.), mix(vec4(1.,.5,.1,1.),vec4(0.1,.5,1.,1.),p.y*.02+.4), pow(glow*2.,4.));        \n\
//gl_FragColor = mix(vec4(1.), mix(vec4(1.,.5,.1,1.),vec4(0.1,.5,1.,1.),p.y*.02+.4), pow(glow*2.,4.));        \n\
\n\
}";
