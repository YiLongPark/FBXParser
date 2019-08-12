//
//  PORSUtil.cpp
//  FBXParser
//
//  Created by beauty-ios-jishu on 2019/8/12.
//  Copyright © 2019 Park. All rights reserved.
//

//#include "PORSUtil.hpp"
//
//namespace Util
//{
//    const PORSElement* getRequiredElement(const PORSElement &element, const string id)
//    {
//        PORSElement* const *iter = &element.mChild;
//
//        while(*iter)
//        {
//            const string temp = string((*iter)->mIDToken.mBegin, (*iter)->mIDToken.mEnd);
//            if(!temp.compare(id))
//            {
//                return *iter;
//            }
//
//            iter = &(*iter)->mSibling;
//        }
//
//        return nullptr;
//    }
//

  

//void triangulate(const vector<int> &old_indices, vector<int> *indices, vector<int> * to_old)
//{
//    assert(indices);
//    assert(to_old);
//
//    int in_polygon_index = 0;
//
//    for(int i = 0; i < old_indices.size(); i++)
//    {
//        int index = old_indices[i];
//        index = index < 0 ? -index - 1 : index;
//
//        if(in_polygon_index <= 2)
//        {
//            indices->push_back(index);
//            to_old->push_back(index);
//        }
//        else
//        {
//            indices->push_back(old_indices[i - in_polygon_index]);
//            to_old->push_back(i - in_polygon_index);
//            indices->push_back(old_indices[i - 1]);
//            to_old->push_back(i - 1);
//            indices->push_back(index);
//            to_old->push_back(i);
//        }
//
//        in_polygon_index++;
//        if(old_indices[i] < 0)
//        {
//            in_polygon_index = 0;
//        }
//    }
//
//}

//}
