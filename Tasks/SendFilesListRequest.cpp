//
// Created by michal on 21.12.18.
//

#include "SendFilesListRequest.h"

Package SendFilesListRequest::getPackage() {
    return {id, operatinoCode};
}