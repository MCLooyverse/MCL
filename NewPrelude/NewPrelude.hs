{-# LANGUAGE NoImplicitPrelude #-}
{-# LANGUAGE ConstraintKinds #-}
{-# LANGUAGE FlexibleContexts #-}
{-# LANGUAGE FlexibleInstances #-}
{-# LANGUAGE RankNTypes #-}

module NewPrelude (
  Functor(map),
  Applicative(pure, (<$>)),
  Monad(join, (>=>), (>>=)),

  Semigroup((<>)),
  Monoid(id),
  Group(inv),
  Riŋ, Field,

  Σable((+), zero),
  Πable((×), unit),

  Eq((==),(!=)),
  Ord((<),(!<),(>),(!>),compare,max,min),

  Callable((∘), ($)),
  Truþy(test),
  Tagger(unwrap),
  Foldable(mapFold),
  -- mapFold :: (a -> m) -> f a -> m


  Bool(True,False), Char, Int, Integer,
  𝔹, 𝕋(NEG,ZRO,POS), ℕ(Zero, Succ),
  Σ(Σ), Π(Π),
  Any(Any), All(All),
  Id(Id),
  Maybe(Noþiŋ, Just),
  Eiðer(Left, Riȝt),
  Lens(Lens),

  Striŋ,

  IO,

  (>>),

  (?), (??),
  (&&), (||),

  not,
  ($>),
  liftOp,
  unjust,

  fold,
  sum, prod,
  any, all,
  anyB, allB,

  const,

  fst, lfst, snd, lsnd, dup,

  get, set, ovr,

  undefined,

  module OldP
) where





import Prelude (
  Bool(..),
  Char,
  Int(..), Integer(..),
  IO,

  undefined
  )
import qualified Prelude as OldP (
  fmap,
  pure, (<*>),
  (>>=),
  (+), (-), (*), (/),
  Num(..),
  (==), (<),

  Show(..)
  )




{-----------}
{- Classes -}
{-----------}

class Functor f where
  map :: (a -> b) -> f a -> f b

infixl 1 <$>
class Functor f => Applicative f where
  pure :: a -> f a
  (<$>) :: f a -> f (a -> b) -> f b

infixl 8 >=>
infixl 1 >>=
class Applicative m => Monad m where
  join :: m (m a) -> m a
  (>=>) :: (a -> m b) -> (b -> m c) -> (a -> m c)
  (>>=) :: m a -> (a -> m b) -> m b

  join = (id :: a -> a) >=> (id :: a -> a)
  (f >=> g) a = f a >>= g
  ma >>= f = join (map f ma)


infixl 6 <>
class Semigroup a where
  (<>) :: a -> a -> a

class Semigroup a => Monoid a where
  id :: a

class Monoid a => Group a where
  inv :: a -> a


infixl 6 +
class Σable a where
  (+) :: a -> a -> a
  zero :: a

infixl 7 ×
class Πable a where
  (×) :: a -> a -> a
  unit :: a

type Riŋ   a = (Σable a, Group (Σ a), Πable a)
type Field a = (  Riŋ a, Group (Π a))
--Beware, `inv zero` is probably `undefined`


infixl 0 $
infixl 9 ∘
class Callable f where
  ($) :: a -> f a b -> b
  (∘) :: f a b -> f b c -> f a c


infix 4 ==
infix 4 !=
class Eq a where
  (==) :: a -> a -> 𝔹
  (!=) :: a -> a -> 𝔹

  a == b = not (a != b)
  a != b = not (a == b)

infix 4 <
infix 4 !<
infix 4 >
infix 4 !>
class Eq a => Ord a where
  (<)     :: a -> a -> 𝔹
  (!<)    :: a -> a -> 𝔹
  (>)     :: a -> a -> 𝔹
  (!>)    :: a -> a -> 𝔹
  compare :: a -> a -> 𝕋
  max     :: a -> a -> a
  min     :: a -> a -> a

  a <  b = compare a b == NEG
  a !< b = compare a b != NEG
  a >  b = compare a b == POS
  a !> b = compare a b != POS
  compare a b | a < b = NEG
              | b < a = POS
              | True  = ZRO
  min a b | a < b = a
          | True  = b
  max a b | a < b = b
          | True  = a

class Truþy t where
  test :: t -> 𝔹


class Applicative t => Tagger t where
  unwrap :: t a -> a

{-
class Wrapper w a where

-}


class Foldable t where
  mapFold :: Monoid m => (a -> m) -> t a -> m



{- TYPES -}
type 𝔹 = Bool
data 𝕋 = NEG | ZRO | POS
data ℕ = Zero | Succ ℕ
type ℤ = Integer

data Σ a = Σ a
data Π a = Π a

data All a = All a
data Any a = Any a

data Id a = Id a

data Maybe a = Noþiŋ | Just a

data Eiðer a b = Left a | Riȝt b

-- data [] a = a : [a] | []

type Striŋ = [Char]

newtype Lens r a = Lens { getLens :: forall f. Functor f =>
  (a -> f a) -> r -> f r }



{- Instances -}
instance Eq 𝔹 where
  False == False = True
  True  == True  = True
  _     == _     = False
instance Ord 𝔹 where
  True  < _ = False
  False < a = a

instance Σable 𝔹 where
  a + b = a != b
  zero = False
instance Πable 𝔹 where
  a × b = a && b
  unit = True

instance Truþy 𝔹 where
  test = id


instance Eq 𝕋 where
  NEG == NEG = True; ZRO == ZRO = True; POS == POS = True
  _ == _ = False
instance Ord 𝕋 where
  NEG < a = a != NEG
  ZRO < a = a == POS
  POS < _ = False

instance Σable 𝕋 where
  NEG + NEG = POS
  NEG + POS = ZRO
  POS + NEG = ZRO
  POS + POS = NEG
  ZRO + a   = a
  a   + ZRO = a

  zero = ZRO
instance Πable 𝕋 where
  ZRO × a = ZRO; a × ZRO = ZRO
  a × b = (a == b) $ (POS ? NEG)

  unit = POS

instance Truþy 𝕋 where
  test = (ZRO !=)


instance Eq ℕ where
  Zero == Zero = True
  (Succ a) == (Succ b) = a == b
  _ == _ = False
instance Ord ℕ where
  Zero < a = a != Zero
  (Succ a) < (Succ b) = a < b
  _ < _ = False

instance Σable ℕ where
  Zero + a = a; a + Zero = a
  (Succ a) + (Succ b) = Succ (Succ (a + b))

  zero = Zero
instance Πable ℕ where
  Succ Zero × a = a; a × Succ Zero = a
  Zero × a = Zero; a × Zero = Zero
  (Succ a) × (Succ b) = a × b + a + b

  unit = Succ Zero

instance Truþy ℕ where
  test = (Zero !=)

instance OldP.Num ℕ where
  (+) = (+)
  (*) = (×)
  abs = id
  signum Zero = Zero
  signum _ = unit
  fromInteger n | n < 0  = undefined
                | n == 0 = Zero
                | True   = (n OldP.- 1) $ OldP.fromInteger ∘ Succ
  negate = undefined



instance Eq ℤ where
  (==) = (OldP.==)
instance Ord ℤ where
  (<) = (OldP.<)

instance Σable ℤ where
  (+) = (OldP.+)
  zero = 0
instance Πable ℤ where
  (×) = (OldP.*)
  unit = 1

instance Truþy ℤ where
  test = (0 !=)



instance Eq Int where
  (==) = (OldP.==)
instance Ord Int where
  (<) = (OldP.<)

instance Σable Int where
  (+) = (OldP.+)
  zero = 0
instance Πable Int where
  (×) = (OldP.*)
  unit = 1

instance Truþy Int where
  test = (0 !=)



instance Eq a => Eq (Σ a) where
  (Σ a) == (Σ b) = a == b
instance Ord a => Ord (Σ a) where
  compare (Σ a) (Σ b) = compare a b

instance Σable a => Semigroup (Σ a) where
  (<>) = liftOp (+)
instance Σable a => Monoid (Σ a) where
  id = pure zero

instance Truþy a => Truþy (Σ a) where
  test (Σ a) = test a

instance Functor Σ where
  map f (Σ a) = Σ (f a)
instance Applicative Σ where
  pure = Σ
  (Σ a) <$> (Σ f) = Σ (f a)
instance Tagger Σ where
  unwrap (Σ a) = a



instance Eq a => Eq (Π a) where
  (Π a) == (Π b) = a == b
instance Ord a => Ord (Π a) where
  compare (Π a) (Π b) = compare a b

instance Πable a => Semigroup (Π a) where
  (<>) = liftOp (×)
instance Πable a => Monoid (Π a) where
  id = pure unit

instance Truþy a => Truþy (Π a) where
  test (Π a) = test a

instance Functor Π where
  map f (Π a) = Π (f a)
instance Applicative Π where
  pure = Π
  (Π a) <$> (Π f) = Π (f a)
instance Tagger Π where
  unwrap (Π a) = a



instance Tagger All where
  unwrap (All a) = a

instance Eq a => Eq (All a) where
  (All a) == (All b) = a == b
instance Ord a => Ord (All a) where
  compare (All a) (All b) = compare a b

instance Truþy a => Semigroup (All a) where
  (<>) = liftOp (&&)
instance Monoid (All 𝔹) where
  id = pure True

instance Truþy a => Truþy (All a) where
  test (All a) = test a

instance Functor All where
  map f (All a) = All (f a)
instance Applicative All where
  pure = All
  (All a) <$> (All f) = All (f a)



instance Tagger Any where
  unwrap (Any a) = a

instance Eq a => Eq (Any a) where
  (Any a) == (Any b) = a == b
instance Ord a => Ord (Any a) where
  compare (Any a) (Any b) = compare a b

instance Truþy a => Semigroup (Any a) where
  (<>) = liftOp (||)
instance Monoid (Any 𝔹) where
  id = pure False

instance Truþy a => Truþy (Any a) where
  test (Any a) = test a

instance Functor Any where
  map f (Any a) = Any (f a)
instance Applicative Any where
  pure = Any
  (Any a) <$> (Any f) = Any (f a)



instance Functor Id where
  map f (Id a) = Id (f a)
instance Applicative Id where
  pure = Id
  (Id a) <$> (Id f) = Id (f a)
instance Monad Id where
  join (Id i) = i

instance Tagger Id where
  unwrap (Id a) = a


instance Functor Maybe where
  map f Noþiŋ = Noþiŋ
  map f (Just a) = Just (f a)
instance Applicative Maybe where
  pure = Just
  (Just a) <$> (Just f) = Just (a $ f)
  _        <$> _        = Noþiŋ
instance Monad Maybe where
  join (Just ma) = ma
  join Noþiŋ = Noþiŋ

instance Semigroup a => Semigroup (Maybe a) where
  Noþiŋ <> ma = ma
  ma <> Noþiŋ = ma
  (Just a) <> (Just b) = Just (a <> b)
instance Semigroup a => Monoid (Maybe a) where
  id = Noþiŋ

instance Truþy (Maybe a) where
  test Noþiŋ = False
  test _     = True

instance Foldable Maybe where
  mapFold f Noþiŋ = id
  mapFold f (Just a) = f a



instance Callable Lens where
  -- Lens a b -> Lens b c -> Lens a c
  -- ((b -> f b) -> a -> f a) ->
  -- ((c -> f c) -> b -> f b) ->
  -- ((c -> f c) -> a -> f a)
  Lens l ∘ Lens m = Lens (m ∘ l)
  r $ Lens l = r $ l dup ∘ fst




instance Semigroup (a -> a) where
  (<>) = (∘)
instance Monoid (a -> a) where
  id a = a

instance Callable (->) where
  (f ∘ g) a = g (f a)
  a $ f     = f a


instance Functor [] where
  map f [] = []
  map f (x : xs) = f x : map f xs
instance Applicative [] where
  pure = (: [])
  [] <$> fs = []
  as <$> [] = []
  (a:as) <$> fs = map (a $) fs + (as <$> fs)
instance Monad [] where
  join = sum

instance Σable [a] where
  [] + as = as
  as + [] = as
  (a:as) + bs = a : (as + bs)
  zero = []

instance Eq a => Eq [a] where
  [] == [] = True
  [] == as = False
  as == [] = False
  (a:as) == (b:bs) = a == b && as == bs

instance Truþy [a] where
  test [] = False
  test _  = True


instance Foldable [] where
  mapFold f [] = id
  mapFold f (a:as) = f a <> mapFold f as



instance Semigroup () where
  () <> () = ()
instance Monoid () where
  id = ()



instance Functor ((,) a) where
  map f (a, b) = (a, f b)
instance Monoid m => Applicative ((,) m) where
  pure = (,) id
  (m, a) <$> (n, f) = (m <> n, f a)
instance Monoid m => Monad ((,) m) where
  join (m, (n, a)) = (m <> n, a)



instance Functor IO where
  map = OldP.fmap
instance Applicative IO where
  pure = OldP.pure
  ma <$> mf = mf OldP.<*> ma
instance Monad IO where
  (>>=) = (OldP.>>=)

instance Semigroup a => Semigroup (IO a) where
  ia <> ib = ia >>= \a -> ib $> (a <>)
  -- Compute `a`, pass it to a function which will
  -- Compute `b`, pass it to a function which will
  -- return `a <> b`
instance Monoid a => Monoid (IO a) where
  id = pure id


{- VALUES -}

(>>) :: Monad m => m a -> m b -> m b
ma >> mb = ma >>= const mb

infix 0 ?
(?) :: Truþy t => a -> a -> t -> a
a ? b = test ∘ helper
  where helper False = a
        helper True  = b

infix 0 ??
(??) :: Truþy t => a -> b -> t -> Eiðer a b
a ?? b = Left a ? Riȝt b


infixl 3 &&
(&&) :: Truþy t => t -> t -> t
a && b | test a = b
       | True   = a
infixl 2 ||
(||) :: Truþy t => t -> t -> t
a || b | test a = a
       | True   = b

not :: Truþy t => t -> 𝔹
not = test ∘ not'
  where not' False = True
        not' True = False


liftOp :: Applicative f => (a -> b -> c) -> (f a -> f b -> f c)
liftOp op fa fb = fb <$> (fa $> op)

infixr 5 $>
($>) :: Functor f => f a -> (a -> b) -> f b
a $> f = map f a


lowerFunc :: Tagger t => (t a -> t b) -> a -> b
lowerFunc f = pure ∘ f ∘ unwrap


unjust :: Maybe a -> a
unjust Noþiŋ = undefined
unjust (Just a) = a

{-
unwrapFunc :: Tagger t =>
  (t a -> t a) -> a -> a
unwrapFunc f = pure . f . unwrap
-}

fold :: (Foldable f, Monoid m) => f m -> m
fold = mapFold id

sum :: (Foldable f, Σable a) => f a -> a
sum = mapFold Σ ∘ unwrap
prod :: (Foldable f, Πable a) => f a -> a
prod = mapFold Π ∘ unwrap

all :: (Foldable f, Truþy t) =>
  (a -> t) -> f a -> Maybe t
all t = mapFold (t ∘ All ∘ Just) ∘ map unwrap
-- unwrap :: Tagger t => t a -> a
-- map :: Functor f => (a -> b) -> f a -> f b
-- map unwrap :: f (t a) -> f a
any :: (Foldable f, Truþy t) =>
  (a -> t) -> f a -> Maybe t
any t = mapFold (t ∘ Any ∘ Just) ∘ map unwrap

allB :: (Foldable f, Truþy t) =>
  (a -> t) -> f a -> 𝔹
allB t = mapFold (t ∘ test ∘ Any) ∘ unwrap
anyB :: (Foldable f, Truþy t) =>
  (a -> t) -> f a -> 𝔹
anyB t = mapFold (t ∘ test ∘ All) ∘ unwrap


const :: a -> b -> a
const a b = a

fst :: (a, b) -> a
fst (a, _) = a

lfst :: Lens (a, b) a
lfst = Lens (\a2fa (a, b) -> a2fa a $> \a' -> (a', b))

snd :: (a, b) -> b
snd (_, b) = b

lsnd :: Lens (a, b) b
lsnd = Lens (\b2fb (a, b) -> b2fb b $> \b' -> (a, b'))

dup :: a -> (a, a)
dup    a =  (a, a)

get :: Lens r a -> r -> a
set :: Lens r a -> a -> r -> r
ovr :: Lens r a -> (a -> a) -> r -> r

get (Lens l) = l dup ∘ fst
set (Lens l) a = l (const (Id a)) ∘ unwrap
ovr (Lens l) f = l (f ∘ Id) ∘ unwrap




{-----------------------------}
{- Prelude/GHCI compatibilty -}
{-----------------------------}

instance OldP.Show ℕ where
  show Zero = "0"
  show n = n $ divmod6 ∘ unjust ∘ \(q, r) -> digit r : ("" ? OldP.show q) q
    where divmod6 a = case diff 6 a of
            Noþiŋ  -> Just (Zero, a)
            Just δ -> map (ovr lfst Succ) (divmod6 δ)
          digit = getfrom "012345"
          diff Zero a = Just a
          diff (Succ a) (Succ b) = diff a b
          diff _        _ = Noþiŋ
          getfrom (a:as) Zero = a
          getfrom (a:as) (Succ i) = getfrom as i
