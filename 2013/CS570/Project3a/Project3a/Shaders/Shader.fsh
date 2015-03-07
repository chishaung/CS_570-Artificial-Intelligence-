//
//  Shader.fsh
//  Project3a
//
//  Created by Shaung on 13/3/15.
//  Copyright (c) 2013年 Shaung. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
