

#include "BST.h"
#include "ElementAlreadyExistsInBSTException.h"
#include "ElementDoesNotExistInBSTException.h"

// To be completed!
template<class ElementType>
bool BST<ElementType>::insertR(const ElementType& element,BSTNode<ElementType>* current){
  bool inserted = 0;
  if (current == NULL){
    BSTNode<ElementType>* newP = new BSTNode<ElementType>(element);
    root = newP;
    inserted = 1;
    return inserted;
  }
  if(current->element == element){
    //throw exception
    return 0;
  }
  if(current->element < element){
    if(current->left == NULL){
      BSTNode<ElementType>* newP = new BSTNode<ElementType>(element);
      current->left = newP;
      inserted = 1;
    }
    else{
      inserted = insertR(element, current->left);
    }
    return inserted;
  }
  else{
    if(current->right == NULL){
      BSTNode<ElementType>* newP = new BSTNode<ElementType>(element);
      current->right = newP;
      inserted = 1;
    }
    else{
      inserted = insertR(element, current->right);
    }
    return inserted;
  }

}


template <class ElementType>
int BST<ElementType>::heightR(BSTNode<ElementType>* aNode) const {
  if(aNode ==NULL)
  {
    return 0;
  }
int leftHeight=heightR(aNode.left);
int rightHeight =heightR(aNode.right);

  if (leftHeight>rightHeight){
    return leftHeight+1;

  }
else{
  return rightHeight+1;
}
}
template <class ElementType>
ElementType& BST<ElementType>::retrieveR(const ElementType& targetElement, BSTNode<ElementType>* current) const throw(ElementDoesNotExistInBSTException){

  if(current == NULL)
    throw ElementDoesNotExistInBSTException();

  if(current->element == targetElement){
    return current->element;
  }
  if(current->element < targetElement){
    try{
      return retrieveR(targetElement, current->left);
    }
    catch(ElementDoesNotExistInBSTException){
      throw ElementDoesNotExistInBSTException();
    }
  }
  else{
    try{
      return retrieveR(targetElement, current->right);
    }
    catch(ElementDoesNotExistInBSTException){
      throw ElementDoesNotExistInBSTException();
    }

  }

}

template <class ElementType>
void BST<ElementType>::traverseInOrderR(void visit(ElementType&), BSTNode<ElementType>* current) const{
  if (current == NULL) return;
  traverseInOrderR(visit, current->left);
  ElementType theItem = current->element;
  visit(theItem);
  traverseInOrderR(visit, current->right);
  return;
}

template<class ElementType>
BSTNode<ElementType>* BST<ElementType>::copyTree(const BSTNode<ElementType>* treePtr)const{
  if(treePtr == NULL) return NULL;
  BSTNode<ElementType>* newNode = new BSTNode<ElementType> (treePtr->element);
  newNode->left = copyTree(treePtr->left);
  newNode->right = copyTree(treePtr->right);
  return newNode;

}
template<class ElementType>
void BST<ElementType>::destroyTree(BSTNode<ElementType>* subTreePtr){
  if(subTreePtr == NULL) return;        //make sense using postorder travere,
                                        //you can only delete the node after visiting its children
  destroyTree(subTreePtr->left);
  destroyTree(subTreePtr->right);
  delete subTreePtr;
  return;
}

template <class ElementType>
BST<ElementType>::BST(){
  elementCount = 0;
  root = NULL;
}
template <class ElementType>                           // Default constructor
BST<ElementType>::BST(ElementType& element){
  BSTNode<ElementType>* newroot = new BSTNode<ElementType>;
  newroot->element = element;
  elementCount = 1;
  root = newroot;
}           // Parameterized constructor

template<class ElementType>
BST<ElementType>::BST(const BST<ElementType>& aBST){
  //preorder traverse and then insert each term visited
  root = copyTree(aBST.root);             //why is this ok?? root is private textbook P463
  elementCount = aBST->getElementCount();

}   // Copy constructor

template<class ElementType>         // Destructor
BST<ElementType>::~BST(){
  destroyTree(root);
  elementCount = 0;
}

template<class ElementType>
int BST<ElementType>::getElementCount()const{
  return elementCount;
}

template<class ElementType>
void BST<ElementType>::insert(const ElementType& newElement) throw(ElementAlreadyExistsInBSTException){
  if (insertR(newElement,root) == 0)
    throw ElementAlreadyExistsInBSTException("element already exixts.");
  elementCount++;
}

template<class ElementType>
ElementType& BST<ElementType>::retrieve(const ElementType& targetElement) const throw(ElementDoesNotExistInBSTException){
  try{
    return retrieveR(targetElement, root);
  }
  catch(ElementDoesNotExistInBSTException){
    throw ElementDoesNotExistInBSTException("element does not exist in BST");
  }
}

template<class ElementType>
void BST<ElementType>::traverseInOrder(void visit(ElementType&)) const{
  traverseInOrderR(visit,root);
}
template<class ElementType>
int BST<ElementType>::height() const{
   BST<ElementType>* node=root;
  return heightR(node);
}
