-- Promote types to kinds
{-# LANGUAGE DataKinds #-}
-- Be explicit using ^^^
{-# LANGUAGE KindSignatures #-}
-- Arbitrary functions on types
{-# LANGUAGE TypeFamilies #-}
-- Allow Symbols
{-# LANGUAGE TypeOperators #-}

{-# LANGUAGE UndecidableInstances #-}

{-# LANGUAGE TypeApplications #-}

{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleInstances #-}

{-# LANGUAGE GADTs #-}

{-# LANGUAGE RankNTypes #-}

{-# LANGUAGE ScopedTypeVariables #-}

{-# LANGUAGE AllowAmbiguousTypes #-}

{-# LANGUAGE PolyKinds #-}

{-# LANGUAGE FunctionalDependencies #-}

module TypeLevelNats where
  import Prelude()
  import NewPrelude hiding (Tagger(..))

  import qualified Prelude as OldP (Show(..))

  import Modulo


  type family (a :: ℕ) + (b :: ℕ) where
    'Zero + b = b
    'Succ a + b = 'Succ (a + b)
  type family (a :: ℕ) × (b :: ℕ) where
    'Zero × _ = 'Zero
    'Succ a × b = b + (a × b)

  type S0 = 'Zero
  type S1 = 'Succ S0
  type S2 = 'Succ S1
  type S3 = 'Succ S2
  type S4 = 'Succ S3
  type S5 = 'Succ S4

  type (a :: ℕ) ¦ (b :: ℕ) = a + b+b+b+b+b+b



  type family Compare (a :: ℕ) (b :: ℕ) where
    Compare a    a = ZRO
    Compare Zero a = POS
    Compare a Zero = NEG
    Compare (Succ a) (Succ b) = Compare a b


  class (a :: ℕ) < (b :: ℕ)
  instance (Compare a b ~ POS) => a < b



  newtype (f ∘ g) a = Comp (f (g a))



  type family a ^ (n :: ℕ) where
    a ^ 'Zero = ()
    a ^ 'Succ n = (a, a ^ n)



  {-
  pass0 :: r -> (r -> z) -> z
  pass1 :: (a -> r) -> (r -> z) -> (a -> z)
  pass2 :: (a -> b -> r) -> (r -> z) -> (a -> b -> z)
  -}

  {-
  data IList a = Sing a
               | a :⍪ (InhabitedList a)
  -}


  type family ChangeUnit f r where
    ChangeUnit () r = r
    ChangeUnit (a -> f) r = a -> ChangeUnit f r

  type family CurryIn t where
    CurryIn () = ()
    CurryIn (a, b) = a -> CurryIn b

  type family Curry f where
    Curry (() -> r) = r
    Curry ((a, b) -> r) = a -> Curry (b -> r)




  type family ChangeRet (n :: ℕ) f r where
    ChangeRet 'Zero f r = r
    ChangeRet ('Succ n) (a -> f) r = a -> ChangeRet n f r
  type family GetRet (n :: ℕ) f where
    GetRet 'Zero f = f
    GetRet ('Succ n) (a -> f) = GetRet n f


  class OrderAtLeast (n :: ℕ) f where
    pass :: f -> (forall z. (GetRet n f -> z) -> ChangeRet n f z)

  instance OrderAtLeast n r => OrderAtLeast ('Succ n) (a -> r) where
    pass f g a = pass @n (f a) g
  instance OrderAtLeast 'Zero r where
    pass r g = g r





  data Mod (n :: ℕ) where
    MZero :: Zero < n => Mod n
    MSucc ::
  data Vector (n :: ℕ) a where
    Vec0 :: Vector 'Zero a
    (:>) :: a -> Vector n a -> Vector ('Succ n) a


  instance Functor (Vector n) where
    map f Vec0 = Vec0
    map f (a :> v) = f a :> map f v
  instance Foldable (Vector n) where
    mapFold f Vec0 = id
    mapFold f (a :> v) = f a <> mapFold f v


  data Matrix (width :: ℕ) (height :: ℕ) a where
    Mat0 :: Matrix w Zero a
    (:#) :: Vector w a -> Matrix w h a -> Matrix w (Succ h) a

  factorMat :: Matrix w h a -> Vector h (Vector w a)
  factorMat Mat0 = Vec0
  factorMat (r :# m) = r :> factorMat m


  swap :: (a -> b -> c) -> b -> a -> c
  swap f a b = f b a

  foldr :: Foldable f => (b -> a -> b) -> b -> f a -> b
  foldr f i l = mapFold (swap f) l i

  instance OldP.Show a => OldP.Show (Vector n a) where
    show Vec0 = "{}"
    show (a :> v) = "{ " +
      foldr (\m n -> OldP.show m + ", " + OldP.show n) (OldP.show a) v +
      " }"

  instance OldP.Show a => OldP.Show (Matrix w h a) where
    show = factorMat ∘ OldP.show



  infix 7 ⋅
  (⋅) :: (Σable a, Πable a) => Vector n a -> Vector n a -> a
  Vec0 ⋅ Vec0 = zero
  (a :> v) ⋅ (a' :> v') = a × a' + v ⋅ v'

  data DNat (n :: ℕ) where
    DZero :: DNat Zero
    DSucc :: DNat n -> DNat (Succ n)

  class Wrapper w a | w -> a where
    wrapper :: Lens w a
    unwrap :: w -> a
    wrap :: a -> w

    unwrap = get wrapper
    wrapper = Lens (\f r -> f (unwrap r) $> wrap)

  class Constant c a | c -> a where
    getconst :: c -> a

  instance Constant (DNat n) ℕ where
    getconst DZero = Zero
    getconst (DSucc n) = Succ (getconst n)

  instance OldP.Show (DNat n) where
    show = getconst ∘ OldP.show


  class DemoteNat s where
    demoteNat :: DNat s

  instance DemoteNat Zero where
    demoteNat = DZero
  instance DemoteNat n => DemoteNat (Succ n) where
    demoteNat = DSucc (demoteNat @n)

  {-
  lvec :: forall (i :: ℕ) (n :: ℕ) a. i < n => Lens (Vector n a) a
  lvec = case
  -}

  row :: ℕ -> Matrix w h a -> Vector w a
  row Zero (r :# m) = r
  row (Succ n) (r :# m) = row n m
  row _ _ = undefined

  col :: ℕ -> Matrix w h a -> Vector h a
  col Zero (


  --(*) :: (Σable a, Πable a) => Matrix w j a -> Matrix j h a -> Matrix w h a


module SuperType (SuperType(..)) where
  import Prelude()
  import NewPrelude

  class SuperType s a where
    inject :: a -> s
    restrict :: s -> Maybe a


  class (SuperType s' s, SuperType s a) => SuperType s' a where
    inject = inject ∘ inject
    restrict = restrict >=> restrict


module ModNat (ModNat()) where
  import Prelude()
  import NewPrelude
  import SuperType


  newtype ModNat (n :: ℕ) = ModNat ℕ

  instance SuperType ℕ (ModNat Zero) where
    inject
  instance SuperType ℕ (ModNat n) where
    inject (ModNat n) = n
    restrict n
