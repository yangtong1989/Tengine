/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2018, Open AI Lab
 * Author: chunyinglv@openailab.com
 */
#include "operator/reorg.hpp"

namespace TEngine {
bool Reorg::InferShape(const std::vector<TEngine::TShape>& ishape, std::vector<TEngine::TShape>& oshape, int layout)
{
    const TShape& input = ishape[0];
    int n = input.GetN();
    int c = input.GetC();
    int h = input.GetH();
    int w = input.GetW();

    TShape shape;
    int stride = param_.stride;
    std::vector<int> dim = {n, c * (stride * stride), h / stride, w / stride};

    shape.SetDim(dim);
    shape.SetDataLayout(input.GetDataLayout());

    oshape[0] = shape;
    return true;
}

void Reorg::SetSchema(void)
{
    Input({"input:float32"}).Output({"output:float32"}).SetAttr("stride", 1).SetDoc(R"DOC(Reorg Operator)DOC");
}

}    // namespace TEngine
